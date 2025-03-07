#pragma once

/* kqueue(2) */
#include <sys/event.h>
#include <sys/time.h>

#include <vector>
#include <deque>
#include <set>

// class Connection;
// class Server;

class KQueueManager
{
    public:
    friend class Server;
    std::vector<struct kevent>  eventlist;

    private:
    int                         capacity;
    int                         nevents;
    const int                   kq;

    public:
    /* registers for a single event; returns -1 on error */
    int                         listen_event(const int ident, const short filter, const unsigned short flags);

    /* returns a non-blocking listening socket descriptor
    bound to the specified port; -1 on error. */
    static int                  open_listenfd(const char *portstr);

    /* returns a non-blocking connection socket descriptor;
    -1 on error. */
    int                         accept_node(const int listenfd, std::string &ipaddr);

    /* returns number of kernel-detected events. returns -1 on error
    newq: newly accepted sockets during previous event loop cycle -- enable reads; disable writes
    sendq: sockets w/ data to send for current elc -- enable writes
    sentq: sockets w/ data sent during previous elc -- disable writes */
    int                         retrieve_events(std::deque<int> &newq, std::set<int> &sendq, std::deque<int> &sentq);

    private:
    /* adjust eventlist capacity */
    void                        _adjust_capacity();

    public:
    KQueueManager();
    ~KQueueManager();

    private:
    KQueueManager(const KQueueManager &other);              /* delete */
    KQueueManager   &operator=(const KQueueManager &rhs);   /* delete */

};
