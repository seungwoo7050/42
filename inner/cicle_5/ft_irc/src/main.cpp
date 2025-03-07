#include "inc/KQueueManager.hpp"
#include "inc/Server.hpp"
#include "inc/debug.hpp"

#include <signal.h>

int main(int ac, char *av[])
{
	debug::check_leaks_atexit(av[0]);

	if (ac != 3)
	{
		std::cerr << "usage: " << av[0] << " <port> <password>" << std::endl;
		return 1;
	}

	struct sigaction act;
	std::memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;

	if (sigaction(SIGPIPE, &act, NULL) == -1
		|| sigaction(SIGQUIT, &act, NULL) == -1
		|| sigaction(SIGTSTP, &act, NULL) == -1
		|| sigaction(SIGINT, &act, NULL) == -1)
	{
		std::cerr << "fatal: sigaction: " << std::strerror(errno) << std::endl;
		return 1;
	}

	try
	{
		Server server(av[1], av[2]);
		server.run();
	}
	catch(const std::invalid_argument &e)
	{
		std::cerr << av[0] << ": " << e.what() << std::endl;
		return 1;
	}
	catch(const std::exception &e)
	{
		std::cerr << av[0] << ": fatal: " << e.what() << std::strerror(errno) << std::endl;
		return 1;
	}
}
