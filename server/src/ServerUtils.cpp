#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Utils.hpp"
#include "Server.hpp"
#include "MoveSystem.hpp"
#include "FightSystem.hpp"
#include "CombatComponent.hpp"
#include "ScoreComponent.hpp"
#include "PositionComponent.hpp"
#include "GraphicalComponent.hpp"

void Network::Server::analyse_header()
{
	rtype::Move sys(&_engine);
	std::lock_guard<std::mutex> guard(_mutex);
	std::pair<int, int> decomposed_header = std::make_pair(((header / 10) % 10), header % 10);

	for (int i = 0; i < 350; i += 1)
		floatcom._arr[i] = 0;
	if (decomposed_header.first >= 0 && decomposed_header.first <= 4) {
		if (decomposed_header.first == 0 && decomposed_header.second == 0)
			add_users();
		if (decomposed_header.second == 1)
			launch_game(decomposed_header.first, decomposed_header.second);
		else if (decomposed_header.second >= 3 && decomposed_header.second <= 7) {
			engineAction(decomposed_header.second, decomposed_header.first);
		}
		if (header != 84)
			send_header();
	}
}

void Network::Server::newMonster(int x, int y, float speed)
{
	ecs::Entity m(_engine.genID() + 1, &this->_engine, ecs::ENEMY);

	m.addComponent(new ecs::Position(x, y, 0, speed, true));
	m.addComponent(new ecs::Combat(1, 1));
	m.addComponent(new ecs::Graphical(ecs::S_MONSTER, x, y));
	_engine.addEntity(m);
}

void Network::Server::spawnEnemies()
{
	auto now = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - _start);

	if (_wave <= 3 && elapsed > std::chrono::seconds(_wave * 8)) {
		switch (_wave) {
			case 0 : enemyWave1(); break;
			case 1 : enemyWave2(); break;
			case 2 : enemyWave3(); break;
			case 3 : enemyWave4(); break;
		}
		_wave += 1;
	} else if (_wave > 3)
		_wave += 1;
	if (_wave > 10) {
		//_wave = 0;
		_start = std::chrono::system_clock::now();
	}
}

void Network::Server::enemyWave1()
{
	int offset = 150;
	int y = HEIGHT / 6;
	int x = LENGTH + 100;

	for (int i = 3; i > 0; i--) {
		newMonster(x, HEIGHT - (y * i), -1);
		newMonster(x + offset, HEIGHT - (y * i), -1);
		newMonster(x + (offset * 2), HEIGHT - (y * i), -1);
		x += offset;
	}
	x -= offset * 2;
	for (int i = 2; i > 0; i--) {
		newMonster(x, (y * i), -1);
		newMonster(x + offset, y * i, -1);
		newMonster(x + (offset * 2), y * i, -1);
		x += offset;
	}
	std::cout << "Spawned enemy wave 1" << std::endl;
}

void Network::Server::enemyWave2()
{
	int offset = 200;
	int y = HEIGHT / 6;
	int x = LENGTH + 100;

	for (int i = 0; i < 3; i++) {
		newMonster(x, HEIGHT - (y * 1), -1);
		newMonster(x, HEIGHT - (y * 2), -1);
		newMonster(x, HEIGHT - (y * 3), -1);
		newMonster(x, HEIGHT - (y * 4), -1);
		newMonster(x, HEIGHT - (y * 5), -1);
		x += offset;
	}

	std::cout << "Spawned enemy wave 2" << std::endl;
}

void Network::Server::enemyWave3()
{
	int offset = 150;
	int y = HEIGHT / 6;
	int x = LENGTH + 100;

	newMonster(x, HEIGHT - (y * 2), -2);
	newMonster(x, HEIGHT - (y * 4), -2);
	x += offset;
	newMonster(x, HEIGHT / 2, -2);
	x += 250;
	newMonster(x, HEIGHT - (y * 1), -2);
	newMonster(x, HEIGHT - (y * 5), -2);
	x += offset;
	newMonster(x, HEIGHT / 2, -2);
	x += offset;
	newMonster(x, HEIGHT - (y * 2), -2);
	newMonster(x, HEIGHT - (y * 4), -2);
	x += offset;
	newMonster(x, HEIGHT / 2, -2);
	x += 250;

	std::cout << "Spawned enemy wave 3" << std::endl;
}

void Network::Server::enemyWave4()
{
	int offset = 200;
	int y = HEIGHT / 6;
	int x = LENGTH + 100;

	newMonster(x, HEIGHT - (y * 1), -2);
	newMonster(x, HEIGHT - (y * 5), -2);
	newMonster(x, HEIGHT / 2, -2);
	x += offset;
	newMonster(x, HEIGHT - (y * 2), -2);
	newMonster(x, HEIGHT - (y * 4), -2);
	x += offset;

	newMonster(x, HEIGHT - (y * 2), -2);
	newMonster(x, HEIGHT - (y * 4), -2);

	x += offset;
	newMonster(x, HEIGHT - (y * 1), -2);
	newMonster(x, HEIGHT - (y * 5), -2);
	newMonster(x, HEIGHT / 2, -2);
	x += offset;
	newMonster(x, HEIGHT - (y * 2), -2);
	newMonster(x, HEIGHT - (y * 4), -2);
	x += offset;
	newMonster(x, HEIGHT / 2, -2);
	std::cout << "Spawned enemy wave 4" << std::endl;
}

void Network::Server::playerDead(int n)
{
	//users.erase(users.begin() + n - 1);
	header = ((n) * 10) + 2;
	std::cout << "player dead : " << header << std::endl;
	floatcom.size = 0;
	send_header();
}

void Network::Server::updateEngine()
{
	std::lock_guard<std::mutex> guard(_mutex);
	spawnEnemies();

	rtype::Move sys(&_engine);
	int index = 0;
	auto entities = _engine.getEntities();

	for (size_t i = 0; i < entities.size(); i++) {
		if (entities[i].getType() != ecs::PLAYER &&
		entities[i].hasComponent(ecs::POSITION) &&
		entities[i].hasComponent(ecs::GRAPHICAL)) {
			index = sys.run(entities[i]);
			if (index != 0 && index != -1)
				return (playerDead(index));
		}
	}
	fillFloatcom();
	send_header();
}

int Network::Server::movePlayer(int x, int y, int n)
{
	int factor = 1;

	auto entity = _engine.getEntities().begin();
	while (entity != _engine.getEntities().end()) {
		if (entity->getType() == ecs::PLAYER && entity->getIndex() == n) {
			ecs::Position add(factor * x, factor * y, 0);
			rtype::Move sys(&_engine);
			if (sys.run(*entity, add) == n)
				playerDead(n);
			fillFloatcom();
			return (0);
		}
		entity += 1;
	}
	fillFloatcom();
	return (-1);
}

int Network::Server::playerAttack(int n)
{
	auto entity = _engine.getEntities().begin();
	while (entity != _engine.getEntities().end()) {
		if (entity->getType() == ecs::PLAYER && entity->getIndex() == n) {
			rtype::Fight sys(&_engine);
			sys.run(*entity);
			fillFloatcom();
			return (0);
		}
		entity += 1;
	}
	fillFloatcom();
	return (-1);
}

int Network::Server::engineAction(int action, int n)
{
	switch (action) {
		case 3 : return (playerAttack(n)); break;
		case 4 : return (movePlayer(0, -1, n)); break;
		case 5 : return (movePlayer(0, 1, n)); break;
		case 6 : return (movePlayer(-1, 0, n)); break;
		case 7 : return (movePlayer(1, 0, n)); break;
	}
	return (0);
}

/*
** spriteType, num, x, y, getAngle
*/

void Network::Server::fillFloatcom()
{
	int index = 0;
	std::map<ecs::entityType, int> nums;
	auto entities = _engine.getEntities();

	nums[ecs::ENEMY] = 1;
	nums[ecs::P_MISSILE] = 1;
	nums[ecs::E_MISSILE] = 1;
	for (size_t i = 0; i < entities.size(); i++) {
		if (entities[i].hasComponent(ecs::POSITION) && entities[i].hasComponent(ecs::GRAPHICAL)) {

			auto pos = dynamic_cast<ecs::Position *>(entities[i].getComponent(ecs::POSITION));
			auto sprite = dynamic_cast<ecs::Graphical *>(entities[i].getComponent(ecs::GRAPHICAL));

			floatcom._arr[index] = (float)sprite->getSpriteType();
			if (entities[i].getType() == ecs::PLAYER)
				floatcom._arr[index + 1] = 1;
			else {
				nums[entities[i].getType()] += 1;
				floatcom._arr[index + 1] = nums[entities[i].getType()];
			}
			floatcom._arr[index + 2] = (float)pos->getPos().x;
			floatcom._arr[index + 3] = (float)pos->getPos().y;
			floatcom._arr[index + 4] = (float)pos->getAngle();
			index += 5;
		}
	}
	floatcom.size = index;
}

void Network::Server::launch_game(int &header_first, int &header_second)
{
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
		_start = std::chrono::system_clock::now();
		header = 1;
		fillFloatcom();
	} else
		header = (header_first * 10) + header_second;
}

void Network::Server::initPlayer(int n)
{
	ecs::Entity p(_engine.genID(), &this->_engine, ecs::PLAYER);

	int offsetY = 150;
	int offsetX = 100;

	p.setIndex(n);
	p.addComponent(new ecs::Position(offsetX, offsetY * n, 0));
	p.addComponent(new ecs::Combat(1, 1));
	p.addComponent(new ecs::Graphical(ecs::S_SHIP1, offsetX, offsetY * n));
	p.addComponent(new ecs::Score());

	auto gr = dynamic_cast<ecs::Graphical *>(p.getComponent(ecs::GRAPHICAL));
	switch (n) {
		case 2: gr->setSpriteType(ecs::S_SHIP2); break;
		case 3: gr->setSpriteType(ecs::S_SHIP3); break;
		case 4: gr->setSpriteType(ecs::S_SHIP4); break;
	}
	_engine.addEntity(p);
	std::cout << "Player " << n << " created!" << std::endl;
}

void Network::Server::add_users()
{
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
			initPlayer(id);
		}
	} else {
		header = 84;
		socket_.send_to(boost::asio::buffer(&header, sizeof(header)), sender_endpoint);
	}
}
