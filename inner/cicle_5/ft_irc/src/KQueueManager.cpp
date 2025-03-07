#include "inc/KQueueManager.hpp"

/* getaddrinfo(3) */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <arpa/inet.h>  // inet_ntoa(3)
#include <fcntl.h>      // fcntl(2)
#include <unistd.h>     // close(3)
#include <cerrno>
#include <cstring>		// std::memset
#include <stdexcept>

int KQueueManager::listen_event(const int ident, const short filter, const unsigned short flags)
{
    struct kevent ev;
    EV_SET(&ev, ident, filter, flags, 0, 0, NULL);

    ++this->nevents;
    return kevent(this->kq, &ev, 1, NULL, 0, NULL);
}

int KQueueManager::open_listenfd(const char *portstr)
{
	addrinfo hints;
	std::memset(&hints, 0, sizeof(addrinfo));

	hints.ai_family = AF_INET;        	// (AF_UNSPEC) use either IPv4 or IPv6 -> use IPv4 (otherwise errno set to EINVAL)
	hints.ai_socktype = SOCK_STREAM;    // stream socket
	hints.ai_protocol = IPPROTO_TCP;    // use TCP

    // accept any addresses | use local IPv | connect using numeric port
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;

	addrinfo *listp = NULL;
	if (int res = getaddrinfo(NULL, portstr, &hints, &listp))
	{
		return -1;
	}

	int listenfd = -1;
	addrinfo *p = listp;
	for (; p; p = p->ai_next)
	{
		if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
			continue; // socket failed, try the next

		int optval = 1;
		if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) < 0  // eliminates "Address already in use" error from bind
			|| bind(listenfd, p->ai_addr, p->ai_addrlen) < 0)
		{
			close(listenfd);
			continue;
		}

		break;
	}

	freeaddrinfo(listp);    // fyi, freeaddrinfo(NULL) is safe.
	if (!p) // no address worked; return error
		return -1;
	
	if (listen(listenfd, 1024) < 0) // make fd a listening socket ready to accept connection requests
	{
		close(listenfd);
		return -1;
	}

	if (fcntl(listenfd, F_SETFL, O_NONBLOCK) == -1)
	{
		close(listenfd);
		return -1;
	}

	return listenfd;
}

int KQueueManager::accept_node(const int listenfd, std::string &ipaddr)
{
    sockaddr_storage	client_addr = {};
    socklen_t			addr_size = sizeof(client_addr);
    
    int clientfd = accept(listenfd, reinterpret_cast<sockaddr *>(&client_addr), &addr_size);
    if (clientfd == -1)
	{
		return -1;
    }

    if (fcntl(clientfd, F_SETFL, O_NONBLOCK) == -1)
	{
		close(clientfd);
		return -1;
	}

	if (client_addr.ss_family == AF_INET)
	{
		sockaddr_in *ipv4 = reinterpret_cast<sockaddr_in *>(&client_addr);
		in_addr addr = ipv4->sin_addr;
		ipaddr = inet_ntoa(addr);
	}
	
    return clientfd;
}

int KQueueManager::retrieve_events(std::deque<int> &newq, std::set<int> &sendq, std::deque<int> &sentq)
{
	const std::size_t newqsize = newq.size(), sendqsize = sendq.size(), sentqsize = sentq.size();
	
    for (std::size_t i = 0; i < newqsize; ++i)
    {
		int sockfd = newq.front();
        EV_SET(&this->eventlist[i], sockfd, EVFILT_READ, EV_ADD | EV_ENABLE | EV_CLEAR, 0, 0, NULL);
        EV_SET(&this->eventlist[newqsize + i], sockfd, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, NULL);
        newq.pop_front();
    }

	this->nevents += newqsize * 2; // count write events in here even though inefficient
	this->_adjust_capacity();

	std::set<int>::iterator cur = sendq.begin();
	for (std::size_t i = newqsize * 2; i < newqsize * 2 + sendqsize; ++i)
	{
		std::set<int>::iterator pre = cur++;
		int sockfd = *pre;
        EV_SET(&this->eventlist[i], sockfd, EVFILT_WRITE, EV_ENABLE, 0, 0, NULL);
		sendq.erase(pre);
	}

	for (std::size_t i = newqsize * 2 + sendqsize; i < newqsize * 2 + sendqsize + sentqsize; ++i)
	{
		int sockfd = sentq.front();
		EV_SET(&this->eventlist[i], sockfd, EVFILT_WRITE, EV_DISABLE, 0, 0, NULL);
		sentq.pop_back();
	}

	timespec time = {};
	time.tv_sec = 10;
	int nev = kevent(this->kq,
						this->eventlist.data(),
						newqsize * 2 + sendqsize + sentqsize,
						this->eventlist.data(),
						this->nevents,
						&time);
    if (nev < 0)
    {
        throw std::runtime_error("kevent: ");
    }

    return nev;
}

KQueueManager::KQueueManager():
eventlist(100), capacity(100), nevents(0), kq(kqueue())
{
    if (this->kq == -1)
    {
        throw std::runtime_error("failed to create a kernel event queue: ");
    }
}

KQueueManager::~KQueueManager()
{
    if (this->kq != -1)
    {
        close(this->kq);
    }
}

void KQueueManager::_adjust_capacity()
{
    if (this->nevents > this->capacity / 2)
    {
        this->capacity *= 2;
        this->eventlist.resize(capacity);
    }
    else if (this->nevents < this->capacity / 3 && this->capacity > 100)
    {
        this->capacity /= 2;
        this->eventlist.resize(capacity);
    }
}
