/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** main
*/

#include "Server.hpp"

int main(int ac, char** av) {
	try {
		if (ac == 1) {
			std::cerr << "Usage: ./server <port> ...\n";
			return 84;
		}
		boost::asio::io_service io_service;
		//std::vector<Network::Server_ptr> list;
		Network::Server server(io_service, std::atoi(av[1]));
		std::thread run_thread([&io_service]() { io_service.run();});

		while (true) {
			if (server.isRunning())
				server.updateEngine();
			std::this_thread::sleep_for(std::chrono::microseconds(500));
		}
		run_thread.join();
	}
	catch (std::exception& e) {
		  std::cerr << "Exception: " << e.what() << "\n";
		  return 84;
	}
	return 0;
}
