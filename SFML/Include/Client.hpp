#pragma once

#include <array>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Graphics.hpp"
#include "SpriteCreator.hpp"
#include "Background.hpp"
#include "Controls.hpp"
#include "Sound.hpp"

using boost::asio::ip::udp;

template<typename T>
struct infos {
	int size;
	std::array<T, 350> _arr;
};

class UDPClient {
public:
	UDPClient(boost::asio::io_service & io_service, const std::string &host, const std::string &port)
		: io_service_(io_service), socket_(io_service, udp::endpoint(udp::v4(), 0))
		{
			//signal(SIGINT, sigHandler);
			udp::resolver resolver(io_service_);
			udp::resolver::query query(udp::v4(), host, port);
			udp::resolver::iterator iter = resolver.resolve(query);
			endpoint_ = *iter;
			memset(&floatcom, 0, sizeof(floatcom));
			for (int i = 0; i < 350; i += 1)
				floatcom._arr[i] = 0;
			floatcom.size = 0;
			send_header(0);
			receive_header();
		}
	~UDPClient() {socket_.close();};
	void receive_header();
	void handle_header(const boost::system::error_code &, size_t);
	void handle_body(const boost::system::error_code &, size_t);
	void send_header(int message);
	void analyse_header();
	static void sigHandler(int s);
	void mainLoop();
	void sendControls();
	void getComponents();
	void handleQuit();
private:
	uint32_t header = 0;
	boost::asio::io_service &io_service_;
	udp::socket socket_;
	udp::endpoint endpoint_;
	Graphics game;
	Sound sound;
	Controls controls;
	infos<float> floatcom;
	std::vector<std::vector<float>> components;
	int open = 1;
	int idClient = 0;
	bool gameover = false;
};
