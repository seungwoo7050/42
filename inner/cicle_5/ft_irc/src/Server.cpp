#include "inc/Server.hpp"

#include "inc/Connection.hpp"
#include "inc/Executor.hpp"
#include "inc/Message.hpp"
#include "inc/Parser.hpp"

#include "inc/debug.hpp"
#include "inc/utils.hpp"

#include <stdexcept>
#include <exception>
#include <deque>
#include <unistd.h>     // close(2)
#include <cstdlib>      // std::strtod
#include <cctype>       // std::iscntrl

const std::string Server::servername = "irc";
const std::string Server::version = "2.0.3";
const std::size_t Server::bufsiz = 8192UL;
const std::string Server::crlf = (IS_DEFINED(NDEBUG) ? "\r\n": "\n");
const std::time_t Server::timeout = 20L;
const std::time_t Server::cutoff = 600L;

const std::string Server::chantypes = "#";
const std::string Server::chanlimit = "#:10";
const std::string Server::prefix = "(o)@";
const std::string Server::nicklen = "30";
const std::string Server::userlen = "12";
const std::string Server::channellen = "32";
const std::string Server::hostlen = "63";
const std::string Server::kicklen = "255";
const std::string Server::topiclen = "307";

void Server::run()
{
	if (this->kqmanager.listen_event(SIGINT, EVFILT_SIGNAL, EV_ADD | EV_ENABLE) < 0
			|| this->kqmanager.listen_event(this->listenfd, EVFILT_READ, EV_ADD | EV_ENABLE) < 0)
		throw std::runtime_error("failed to register events with kqueue: ");
	
	std::clog << this->servername << " has started" << std::endl;

	for (;;) // event loop
	{
		if (this->interrupt)
			break;
		this->_run_event_loop(); // run one cycle
	}

	std::clog << this->servername << " closed!" << std::endl;
}

bool Server::_validate_port(const char *portstr)
{
	char	*endptr;
	double	ret = std::strtod(portstr, &endptr);

	if (*endptr)
		return false;
	if (!(ret > 0 && ret < (2 << 15)))
		return false;
	if (ret != static_cast<double>(static_cast<int>(ret)))
		return false;
	
	return true;
}

bool Server::_validate_password(const char *passwordstr)
{
	do
	{
		if (std::iscntrl(static_cast<unsigned char>(*passwordstr++)))
			return false;
	}
	while (*passwordstr);

	return true;
}

void Server::_run_event_loop()
{
	static std::deque<int> newq;
	static std::deque<int> sentq;

	this->_keep_alive();

	int n = this->kqmanager.retrieve_events(newq, this->sendq, sentq);

	for (int i = 0; i < n; ++i)
	{
		struct kevent	event = kqmanager.eventlist[i];
		int				ident = event.ident;

		if (event.flags & EV_ERROR)
		{
			if (ident == listenfd)
			{
				throw std::runtime_error("failed to retrieve events on the listening port: ");
			}
			else
			{
				std::clog << "an event on socket " << ident
				<< " is in error: " << std::strerror(event.data)
				<< std::endl;

				this->_disconnect(ident);
			}
		}
		else if (event.filter == EVFILT_SIGNAL)
		{
			this->interrupt = true;
		}
		else if (event.filter == EVFILT_READ)
		{
			if (ident == this->listenfd)
			{
				std::string ipaddr;
				int sockfd = kqmanager.accept_node(this->listenfd, ipaddr);
				if (sockfd == -1)
				{
					std::clog << "failed to accept a connection: "
					<< std::strerror(errno) << std::endl;
				}
				else
				{
					std::clog << "connection at " << ipaddr
					<< " has been accepted on socket " << sockfd
					<< std::endl;

					this->_make_connection(sockfd, ipaddr);
					newq.push_back(sockfd);
				}
			}
			else
			{
				std::map<int, std::list<Connection *>::iterator>::iterator find = this->sockdb.find(ident);
				if (find == this->sockdb.end())
					continue;
				Connection *node = *find->second;

				if (event.flags & EV_EOF)
					Executor::to_doom(*this, node, "");

				ssize_t bytes = this->_read_packet(node, event.data);

				if (bytes < 0)
				{
					std::clog
					<< "failed to read a packet on socket " << ident
					<< ": " << std::strerror(errno) << std::endl;

					this->_disconnect(ident);
					continue;
				}
				else if (bytes == 0) // received a truncated message; do nothing
				{
					continue;
				}

				std::vector<Message> batch;
				Parser::make_messages(node->recvbuf, batch);

				Executor::process(*this, node, batch);
				std::clog
				<< "packet on socket " << ident
				<< " has been processed"
				<< std::endl;
			}
		}
		else if (event.filter == EVFILT_WRITE)
		{
			std::map<int, std::list<Connection *>::iterator>::iterator find = this->sockdb.find(ident);
			if (find == this->sockdb.end())
				continue;
				
			Connection *node = *find->second;
			if (this->sockdb.find(ident) == this->sockdb.end())
				continue;
			
			ssize_t bytes = this->_send_packet(node, event.data);
			if (bytes < 0)
			{
				std::clog
				<< "failed to send a reply on socket " << ident
				<< ": " << std::strerror(errno) << std::endl;

				this->_disconnect(ident);
				continue;
			}
			else if (bytes > 0)
			{
				std::clog
				<< "packet has been sent to socket " << ident
				<< std::endl;
			}

			if (node->is_doomed)
				this->_disconnect(ident);
			else
				sentq.push_back(ident);
		}
	}
}

void Server::_keep_alive()
{
	std::time_t now = std::time(NULL);
	if (now < 0)
	{
		std::clog << "keep alive: " << std::strerror(errno) << std::endl;
		return;
	}

	std::list<Connection *>::iterator it = this->nodes.begin();
	std::list<Connection *>::iterator end = this->nodes.end();
	
	while (it != end)
	{
		Connection *link = *it++;
		if (!link->is_pinged && now - link->timestamp > timeout)
		{
			link->is_pinged = true;
			std::clog << "ping sent" << std::endl;
			Executor::dispatch_packet(*this, link, "PING :" + servername + "\r\n");
		}
		else if (link->is_pinged && now - link->timestamp > cutoff)
		{
			std::clog << "socket " << link->sockfd
			<< " is not responding..." << std::endl;
			
			this->_disconnect(link->sockfd);
		}
	}
}

void Server::_make_connection(int sockfd, const std::string &ipaddr)
{
	Connection *node = new Connection(sockfd, ipaddr);
	
	this->nodes.push_front(node);
	this->sockdb.insert(std::pair<int, std::list<Connection *>::iterator>(sockfd, this->nodes.begin()));
}

void Server::_disconnect(int sockfd)
{
	std::map<int, std::list<Connection *>::iterator>::iterator found = sockdb.find(sockfd);
	if (found == sockdb.end())
		return;

	std::list<Connection *>::iterator it = found->second;
	Connection *node = *it;

	sockdb.erase(sockfd);
	if (nickdb.find(node->nickname) != nickdb.end())
		nickdb.erase(node->nickname);

	std::map<std::string, Channel *>::iterator chanit = node->chandb.begin();
	for (; chanit != node->chandb.end(); ++chanit)
	{
		Channel *chan = chanit->second;

		chan->part(node);

		if (chan->clientdb.empty())	// clean up server resources if chan has been made empty
		{
			std::map<std::string, std::list<Channel *>::iterator>::iterator find = this->chandb.find(chan->name);
			this->chans.erase(find->second);
			this->chandb.erase(find);
			delete chan; // delete empty chan
		}
	}

	nodes.erase(it);
	delete node;

	this->kqmanager.nevents -= 2;
	std::clog
	<< "connection on socket " << sockfd
	<< " has been closed" << std::endl;
}

ssize_t Server::_read_packet(Connection *&node, std::size_t len)
{
	node->timestamp = std::time(NULL);
	node->is_pinged = false;
	
	char buf[bufsiz];
	std::memset(buf, 0, sizeof(buf));

	ssize_t bytes = utils::full_recvn(node->sockfd, buf, std::min<std::size_t>(len, bufsiz));
	node->recvbuf += buf;

	debug::log_recv_status(node->sockfd, bytes, node->recvbuf);

	if (node->recvbuf.size() >= crlf.size()
		&& node->recvbuf.rfind(crlf) + crlf.size() == node->recvbuf.size())
	{
		std::clog << "received a packet on socket " << node->sockfd << std::endl;
		return bytes;
	}
	else
	{
		#ifndef NDEBUG
		unsigned lastone = static_cast<unsigned>(node->recvbuf[node->recvbuf.size() - 2]);
		unsigned lasttwo = static_cast<unsigned>(node->recvbuf[node->recvbuf.size() - 1]);
    	std::clog
    	<< debug_sgr_params::bold_red
		<< "no valid command this time...\n\tlast two ASCII's: "
		<< lastone
		<< "\t"
		<< lasttwo
		<< debug_sgr_params::reset
		<< std::endl;
		#endif

		std::clog << "reveived an incomplete packet on socket " << node->sockfd << std::endl;
		return 0;
	}
}

ssize_t Server::_send_packet(Connection *&node, std::size_t maxlen)
{
	if (node->sendbuf.empty())
		return 0;
	
	if (node->sendbuf.size() > maxlen)
	{
		std::clog
		<< "kernel write buffer is not available this time for socket " << node->sockfd
		<< "\nwill retry later..."
		<< std::endl;

		this->sendq.insert(node->sockfd);
		return 0;
	}


	ssize_t bytes = utils::full_sendn(node->sockfd, node->sendbuf.c_str(), node->sendbuf.size());

	debug::log_send_status(node->sockfd, bytes, node->sendbuf);

	node->sendbuf.clear();

	return bytes;
}

Server::Server(const char *portstr, const char *passwordstr) try :
listenfd(_validate_port(portstr) ? -1 : throw std::invalid_argument("inappropriate port number")),
password(_validate_password(passwordstr) ? passwordstr : throw std::invalid_argument("inappropriate password")),
kqmanager(),
interrupt(false),
nodes(),
sockdb(),
nickdb(),
chans(),
chandb(),
sendq()
{
	if ((this->listenfd = KQueueManager::open_listenfd(portstr)) == -1)
		throw std::runtime_error("failed to open a listening port: ");
}
catch (std::invalid_argument &e)
{}
catch (std::runtime_error &e)
{}

Server::~Server()
{
    if (this->listenfd == -1)
        return;

    close(listenfd);

	std::list<Connection *>::iterator it = this->nodes.begin();
	std::list<Connection *>::iterator end = this->nodes.end();

	while (it != end)
	{
		delete (*it++);
	}

	std::list<Channel *>::iterator it2 = this->chans.begin();
	std::list<Channel *>::iterator end2 = this->chans.end();

	while (it2 != end2)
	{
		delete (*it2++);
	}
}
