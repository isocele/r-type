//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#include <iostream>
#include "Graphics.hpp"
#include "Client.hpp"

int main(int ac, char **av)
{
	try {
		if (ac != 3) {
			std::cerr << "Usage: ./client <ip> <port>\n";
			return 84;
		}
		boost::asio::io_service io_service;
		UDPClient client(io_service, av[1], av[2]);
		std::thread run_thread([&] { io_service.run();});
		client.mainLoop();
		run_thread.join();
	}
	catch (std::exception & e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return 84;
	}
	return 0;
}
