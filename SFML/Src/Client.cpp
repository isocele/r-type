#include <atomic>
#include "Client.hpp"

std::atomic<bool> quit(false);    // signal flag

void UDPClient::send_header(int message) {
	// std::cout << "envois [ " << message << " ]" << std::endl;
	socket_.send_to(boost::asio::buffer(&message, sizeof(message)), endpoint_);
}

void UDPClient::receive_header() {
	socket_.async_receive_from(boost::asio::buffer(&header, sizeof(header)), endpoint_,
				   boost::bind(&UDPClient::handle_header, this,
					       boost::asio::placeholders::error,
					       boost::asio::placeholders::bytes_transferred));
}

void UDPClient::handle_header(const boost::system::error_code &ec, size_t bytes) {
	(void)bytes;
	if (!ec && header != 2) {
		socket_.async_receive_from(boost::asio::buffer(&floatcom, sizeof(floatcom)), endpoint_,
					   boost::bind(&UDPClient::handle_body, this,
						       boost::asio::placeholders::error,
						       boost::asio::placeholders::bytes_transferred));
	} else {
		std::cout << "receive failed: " << ec.message() << std::endl;
		receive_header();
	}
}

void UDPClient::handle_body(const boost::system::error_code &ec, size_t bytes) {
	(void)bytes;
	if (!ec) {
		analyse_header();
		receive_header();
	} else {
		std::cout << "receive failed: " << ec.message() << std::endl;
		receive_header();
	}
}

void UDPClient::analyse_header()
{
	if ((header == 10 || header == 20 || header == 30 || header == 40) && !idClient) {
		idClient = header;
	}
	else if (header == 84) {
		std::cout << "Can't connect, there is already 4 players or the game is started..." << std::endl;
		exit(84);
	}
	else if (header == 9) {
		std::cout << "End of game" << std::endl;
		exit(0);
	}
}

void UDPClient::sigHandler(int sig)
{
	std::cout << "Caught signal = " << sig << std::endl;
	quit.store(true);
}

void UDPClient::sendControls()
{
	if (controls.getSpace()) {
		send_header(idClient + 3);
	}
	if (controls.getUp()) {
		send_header(idClient + 4);
	}
	if (controls.getDown()) {
		send_header(idClient + 5);
	}
	if (controls.getLeft()) {
		send_header(idClient + 6);
	}
	if (controls.getRight()) {
		send_header(idClient + 7);
	}
}

void UDPClient::getComponents()
{
	int nb = 0;
	std::vector<float> tmp;

	for (int i = 0; i < floatcom.size; i++) {
		// std::cout << floatcom._arr[i] << " ";
		tmp.push_back(floatcom._arr[i]);
		nb++;
		if (nb == 5) {
			// std::cout << std::endl;
			components.push_back(tmp);
			tmp.clear();
			nb = 0;
		}
	}
}

void UDPClient::handleQuit()
{
	if (quit.load()) {
		send_header(idClient + 2);
		std::cout << "Send quit to server " << std::endl;
		game.close();
		exit(0);
	}
	else if (header == 84) {
		std::cout << "too many players" << std::endl;
		exit(84);
	}
	else if (open == 0)
		exit(0);
}

void UDPClient::mainLoop()
{
	sound.launchTrack(WELCOME);
	while (open && open != 3 && header != 1) {
		handleQuit();
		open = game.startDisplay(floatcom._arr, floatcom.size);
		if (open == 2 || open == 3) {
			send_header(idClient + 1); // send ready state to server;
			std::cout << "send ready" << std::endl;
		}
	}
	sound.stopTrack(WELCOME);
	sound.launchTrack(PKM);
	while (open) {
		getComponents();
		if ((int)header == idClient + 2 || gameover == true)
			gameover = true;
		open = game.display(components, controls, sound, gameover);
		handleQuit();
		components.clear();
		sendControls();
		controls.reset();
	}
}
