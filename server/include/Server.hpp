#pragma once

#include <iostream>
#include <array>
#include <stdlib.h>
#include <mutex>
#include <chrono>
#include <ctime>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "GameEngine.hpp"
#include "MoveSystem.hpp"
#include "FightSystem.hpp"

template<typename T>
struct infos {
	int size;
	std::array<T, 350> _arr;
};

namespace Network {
	using boost::asio::ip::udp;

	class Client
		: public boost::enable_shared_from_this<Client>
	{

	public:
		Client(boost::asio::ip::address ip, unsigned short port, int &id)
			: own_endpoint_(ip, port)
			{id_ = id;};
		int getId() {return id_;};
		bool checkReady() {return is_ready_;};
		void ready_to_play(bool ready) {is_ready_ = ready;};
		udp::endpoint getEndpoint() {return own_endpoint_;};

	private:
		int id_;
		bool is_ready_ = false;
		udp::endpoint own_endpoint_;
	};

	using Client_ptr = boost::shared_ptr<Client>;

	class Server {

	public:

		//network-related functions
		Server(boost::asio::io_service &io_service, int port);
		void start_server();
		void send_header();
		void handle_send_header(const boost::system::error_code &, size_t, int id);
		void handle_send_body(const boost::system::error_code &, size_t);
		void receive_header();
		void handle_read_header(const boost::system::error_code &, size_t);
		void handle_read_body(const boost::system::error_code &, size_t);
		void add_users();
		void analyse_header();
		bool isRunning();

		//game related functions
		void launch_game(int &, int &);
		void fillFloatcom();
		void change_players_position(int &, int &);
		void updateEngine();

	private:

		int id = 0;
		uint32_t header;
		udp::socket socket_;
		udp::endpoint sender_endpoint;
		infos<float> floatcom;
		std::vector<Client_ptr> users;
		bool game_launched_ = false;
		ecs::Engine _engine;
		std::mutex _mutex;
		int _wave = 0;

		//game related functions
		int engineAction(int action, int n);
		int movePlayer(int x, int y, int n);
		int playerAttack(int n);
		void spawnEnemies();
		void initPlayer(int n);
		void enemyWave1();
		void enemyWave2();
		void enemyWave3();
		void enemyWave4();
		void spawnBoss();
		void newMonster(int x, int y, float speed);
		void playerDead(int n);

		std::chrono::system_clock::time_point _start = std::chrono::system_clock::now();
	};

	using Server_ptr = boost::shared_ptr<Server>;
}
