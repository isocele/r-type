#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Utils.hpp"
#include "Server.hpp"
#include "MoveSystem.hpp"
#include "FightSystem.hpp"
#include "CombatComponent.hpp"
#include "PositionComponent.hpp"
#include "GraphicalComponent.hpp"

void Network::Server::analyse_header() {
	std::pair<int, int> decomposed_header = std::make_pair(((header / 10) % 10), header % 10);

	for (int i = 0; i < 250; i += 1)
		floatcom._arr[i] = 0;
	if (decomposed_header.first >= 0 && decomposed_header.first <= 4) {
		if (decomposed_header.first == 0 && decomposed_header.second == 0)
			add_users();
		if (decomposed_header.second == 1)
			launch_game(decomposed_header.first, decomposed_header.second);
		else if (decomposed_header.second >= 3 && decomposed_header.second <= 7)
			//change_players_position(decomposed_header.first, decomposed_header.second);
			//act upon information received
			engineAction(decomposed_header.second, *_players[decomposed_header.first - 1], decomposed_header.first - 1);
		if (header != 84)
			send_header();
	}
}

int Network::Server::movePlayer(int x, int y, ecs::Entity &player, int id)
{
	_missile = false;
	int factor = 1;
	ecs::Position add(factor * x, factor * y, 0);
	//ecs::System sys = dynamic_cast<rtype::Move &>(_engine.getSystem(rtype::MOVE));
	//std::cout << "Starting ECS movement system for player" << std::endl;
	rtype::Move sys(&_engine);
	if (sys.run(player, add) == -1) {
		std::cerr << "Error while moving\n";
		return (-1);
	}
	fillFloatcom();
	id = id * 5;
	auto pos = dynamic_cast<ecs::Position *>(player.getComponent(ecs::POSITION));
	auto sprite = dynamic_cast<ecs::Graphical *>(player.getComponent(ecs::GRAPHICAL));
	if (pos != NULL && sprite != NULL) {
		floatcom._arr[id] = (float)sprite->getSpriteType();
		floatcom._arr[id + 1] = 1;
		floatcom._arr[id + 2] = (float)pos->getPos().x;
		floatcom._arr[id + 3] = (float)pos->getPos().y;
		floatcom._arr[id + 4] = (float)pos->getAngle();
	}
	return (0);
}

int Network::Server::playerAttack(ecs::Entity &player)
{
	//auto sys = dynamic_cast<rtype::Fight &>(_engine.getSystem(ecs::FIGHT));
	if (_missile == true)
		return (-1);
	rtype::Fight sys(&_engine);
	std::cout << "Starting ECS fight system for player" << std::endl;
	_missile = true;
	return (sys.run(player));
}

int Network::Server::engineAction(int action, ecs::Entity &player, int id)
{
	switch (action) {
	case 3 : return (playerAttack(player)); break;
	case 4 : return (movePlayer(0, -1, player, id)); break;
	case 5 : return (movePlayer(0, 1, player, id)); break;
	case 6 : return (movePlayer(-1, 0, player, id)); break;
	case 7 : return (movePlayer(1, 0, player, id)); break;
	}
	return (0);
}

void Network::Server::fillFloatcom() {
	int index = 0;

	for (int i = 0; _players[i] != NULL; i += 1) {
		auto pos = dynamic_cast<ecs::Position *>(_players[i]->getComponent(ecs::POSITION));
		auto sprite = dynamic_cast<ecs::Graphical *>(_players[i]->getComponent(ecs::GRAPHICAL));

		floatcom._arr[index] = (float)sprite->getSpriteType();
		floatcom._arr[index + 1] = 1;
		floatcom._arr[index + 2] = (float)pos->getPos().x;
		floatcom._arr[index + 3] = (float)pos->getPos().y;
		floatcom._arr[index + 4] = (float)pos->getAngle();
		index += 5;
		//type num x y 0 (angle)
	}
	floatcom.size = index;
}

void Network::Server::launch_game(int &header_first, int &header_second) {
	int id = 0;
	size_t i = 0;

	if (users[header_first - 1]->checkReady() == false)
		users[header_first - 1]->ready_to_play(true);
	else
		users[header_first - 1]->ready_to_play(false);
	for (auto &u: users) {
		if (u->checkReady() == true) {
			floatcom._arr[id] = 1;
			i += 1;
		} if (u->checkReady() == false)
			floatcom._arr[id] = 0;
		id += 1;
	}
	if (i == users.size()) {
		std::cout<<"DEBUT DE LA PARTIE\n";
		game_launched_ = true;
		header = 1;
		fillFloatcom();
	} else
		header = (header_first * 10) + header_second;
}

void Network::Server::initPlayer(int n) {
	ecs::Entity p(_engine.genID(), &this->_engine, ecs::PLAYER);
	int offsetY = 150;
	int offsetX = 100;

	p.addComponent(ecs::POSITION, dynamic_cast<ecs::Component &>(*(new ecs::Position(offsetX, offsetY * n, 0))));
	p.addComponent(ecs::COMBAT, dynamic_cast<ecs::Component &>(*(new ecs::Combat(1, 1))));
	p.addComponent(ecs::GRAPHICAL, dynamic_cast<ecs::Component &>(*(new ecs::Graphical(ecs::S_SHIP1, offsetX, offsetY * n))));

	auto gr = dynamic_cast<ecs::Graphical *>(p.getComponent(ecs::GRAPHICAL));
	switch (n) {
		case 2: gr->setSpriteType(ecs::S_SHIP2); break;
		case 3: gr->setSpriteType(ecs::S_SHIP3); break;
		case 4: gr->setSpriteType(ecs::S_SHIP4); break;
	}

	_players[n - 1] = &_engine.addEntity(p);
	std::cout << "Player " << n << " created!" << std::endl;
}

void Network::Server::add_users() {
	bool add_to_list = true;

	if (id < 4 && game_launched_ == false) {
		for (auto &u: users)
			if (sender_endpoint == u->getEndpoint() || sender_endpoint.port() == 0)
				add_to_list = false;
		if (add_to_list == true) {
			Client_ptr new_client(new Client(sender_endpoint.address(),
							 sender_endpoint.port(),
							 id));
			users.push_back(new_client);
			header = (10 * (id + 1));
			floatcom._arr[id] = header;
			floatcom.size = id + 1;
			id += 1;
			// add user entity
			initPlayer(id);
		}
	} else {
		header = 84;
		socket_.send_to(boost::asio::buffer(&header, sizeof(header)), sender_endpoint);
	}
}
