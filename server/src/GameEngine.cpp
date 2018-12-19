/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** ECS Game Engine
*/

#include "GameEngine.hpp"

ecs::Engine::Engine()
	: _idCounter(0), _sysCounter(0), _firstUpdate(true)
{
}

/*
** Entity Management
**
** genID: generate and get ID when
** creating Entity outside of engine class
*/

int ecs::Engine::genID()
{
	return (_idCounter + 1);
}

ecs::Entity &ecs::Engine::newEntity()
{
	_idCounter++;
	_entities.emplace_back(ecs::Entity(_idCounter, this, ecs::STATIC));
	_idCounter += 1;
	return (_entities.back());
}

ecs::Entity &ecs::Engine::newEntity(ecs::entityType type)
{
	_idCounter++;
	_entities.emplace_back(ecs::Entity(_idCounter, this, type));
	_idCounter += 1;
	return (_entities.back());
}

ecs::Entity &ecs::Engine::addEntity(ecs::Entity &entity)
{
	_entities.push_back(entity);
	_idCounter += 1;
	return (_entities.back());
}

bool ecs::Engine::killEntity(Entity &ent)
{
	auto it = _entities.begin();
	while (it != _entities.end()) {
		if (it->getID() == ent.getID()) {
			_entities.erase(it);
			return (true);
		}
		it += 1;
	}
	return (false);
}

bool ecs::Engine::killEntity(int id)
{
	auto it = _entities.begin();
	while (it != _entities.end()) {
		if (it->getID() == id) {
			_entities.erase(it);
			return (true);
		}
		it += 1;
	}
	std::cerr << "Entity not found" << '\n';
	return (false);
}

std::vector<ecs::Entity> &ecs::Engine::getEntities()
{
	return _entities;
}

/*
** System Management
*/

bool ecs::Engine::hasSystem(ecs::sysType sys)
{
	auto it = _systems.begin();
	while (it != _systems.end()) {
		if (it->getType() == sys)
			return (true);
	}
	return (false);
}

ecs::System &ecs::Engine::getSystem(ecs::sysType sys)
{
	std::cout << "\nSystem Index is " << (int)sys << "\n\n";
	return (_systems[(int)sys]);
}

ecs::System &ecs::Engine::newSystem(ecs::sysType type)
{
	_sysCounter++;
	_systems.emplace_back(ecs::System(type, this));
	return (_systems.back());
}

ecs::System &ecs::Engine::newSystem(ecs::sysType type, System& sys)
{
	_sysCounter++;
	(void)(type);
	//add check of pos here;
	_systems.emplace_back(sys);
	return (_systems.back());
}

bool ecs::Engine::killSystem(int id)
{
	auto it = _systems.begin();
	while (it != _systems.end()) {
		if (it->getType() == id) {
			_systems.erase(it);
			return (true);
		}
	}
	std::cerr << "System not found" << '\n';
	return (false);
}

/*
** OBSOLETE!
*/

ecs::Entity &ecs::Engine::getEntity(int id)
{
	auto it = _entities.begin();
	while (it != _entities.end()) {
		if (it->getID() == id)
			return (*it);
	}
	return (*it);
}
