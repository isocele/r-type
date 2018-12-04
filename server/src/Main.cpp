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
		std::vector<Network::Server_ptr> list;

		// for (int i = 1; i < ac; i += 1) {
			// std::cout << "oui" << '\n';
			Network::Server new_server(io_service, std::atoi(av[1]));
			std::thread run_thread([&io_service]() { io_service.run();});
			// list.push_back(new_server);
		// }
		run_thread.join();
	}
	catch (std::exception& e) {
		  std::cerr << "Exception: " << e.what() << "\n";
		  return 84;
	}
	return 0;
}
