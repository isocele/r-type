/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** ECS Entity
*/

#include <stdexcept>
#include "GameEngine.hpp"
#include "Entity.hpp"

ecs::Entity::Entity(int id, Engine *parent, entityType type)
	: _id(id), _index(0), _parent(parent), _type(type)
{
	if (_type == ecs::PLAYER)
		std::cout << "player BORN" << std::endl;
}

ecs::Entity::~Entity()
{
	//if (_type == ecs::PLAYER)
	//	std::cout << "player DEAD" << std::endl;
}

int ecs::Entity::getID()
{
	return (_id);
}

int ecs::Entity::getIndex()
{
	return (_index);
}

ecs::Engine *ecs::Entity::getParent()
{
	return (_parent);
}

ecs::entityType ecs::Entity::getType()
{
	return _type;
}

void ecs::Entity::setIndex(int index)
{
	_index = index;
}

bool ecs::Entity::hasComponent(const ecs::compType type)
{
	auto comp = _components.begin();
	while (comp != _components.end() && (*comp)->getType() != type)
		comp += 1;
	if (comp != _components.end())
		return (true);
	std::cout << "Entity " << _id << ": Component " << (int)type << " not found" << std::endl;
 	return (false);
}

/*
** the 2 following functions should only be called after hasComponent
*/

ecs::Component *ecs::Entity::getComponent(const ecs::compType type)
{
	auto comp = _components.begin();
	while (comp != _components.end() && (*comp)->getType() != type)
		comp += 1;
	if (comp == _components.end())
		throw("No such Component");
	return (*comp);
}


void ecs::Entity::addComponent(ecs::Component *comp)
{
	_components.emplace_back(comp);
}

void ecs::Entity::updateComponent(ecs::compType type, ecs::Component *updated)
{
	auto comp = _components.begin();
	while (comp != _components.end() && (*comp)->getType() != type)
		comp += 1;
	if (comp != _components.end())
		*comp = updated;
}

void ecs::Entity::removeComponent(ecs::compType type)
{
	auto comp = _components.begin();
	while (comp != _components.end() && (*comp)->getType() != type)
		comp += 1;
	if (comp == _components.end())
		throw("No such Component");
	else
		_components.erase(comp);
}
