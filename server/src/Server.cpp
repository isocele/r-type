#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Server.hpp"

Network::Server::Server(boost::asio::io_service &io_service, int port)
	: socket_(io_service, udp::endpoint(udp::v4(), port)), _missile(false)
{
	memset(&floatcom, 0, sizeof(floatcom));
	_engine.newSystem(ecs::MOVE, dynamic_cast<ecs::System &>(*(new rtype::Move(&_engine))));
	_engine.newSystem(ecs::FIGHT, dynamic_cast<ecs::System &>(*(new rtype::Fight(&_engine))));
	start_server();
}

void Network::Server::start_server()
{
	for (int n = 0; n < 4; n++)
		_players.push_back(NULL);
	receive_header();
	while (game_launched_ == true) {
		_engine.update();
		send_header();
	}
}

void Network::Server::receive_header() {
	socket_.async_receive_from(boost::asio::buffer(&header, sizeof(header)), sender_endpoint,
				   boost::bind(&Server::handle_read_header, this,
					       boost::asio::placeholders::error,
					       boost::asio::placeholders::bytes_transferred));
}

void Network::Server::handle_read_header(const boost::system::error_code &ec, size_t bytes) {
	if (!ec) {
		//std::cout << "reçus [ " << header << " ] size(" << bytes << "bytes)" << std::endl;
		analyse_header(); // ECS actions
		receive_header();
	} else {
		//std::cout << "receive failed: " << ec.message() << std::endl;
		receive_header();
	}
}

void Network::Server::send_header() {
	id = 0;

	for (auto &u: users) {
		socket_.async_send_to(boost::asio::buffer(&header, sizeof(header)), u->getEndpoint(),
				      boost::bind(&Server::handle_send_header, this,
						  boost::asio::placeholders::error,
						  boost::asio::placeholders::bytes_transferred, id));
		id += 1;
	}
}

void Network::Server::handle_send_header(const boost::system::error_code &ec, size_t bytes, int id) {
	if (!ec) {
		//std::cout << "envois [ "<< header << " ] size(" << bytes << " bytes)" << std::endl;
			socket_.async_send_to(boost::asio::buffer(&floatcom, sizeof(floatcom)), users[id]->getEndpoint(),
					      boost::bind(&Server::handle_send_body, this,
							  boost::asio::placeholders::error,
							  boost::asio::placeholders::bytes_transferred));
	}
	else {
		std::cout << "send failed: " << ec.message() << std::endl;
		receive_header();
	}
}

void Network::Server::handle_send_body(const boost::system::error_code &ec, size_t bytes) {
	if (ec) {
		std::cout << "send failed: " << ec.message() << " && bytes : "<< bytes <<std::endl;
		receive_header();
	}
}
