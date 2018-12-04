/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** ECS Entity
*/

#include "GameEngine.hpp"
#include "Entity.hpp"

ecs::Entity::Entity(int id, Engine *parent, entityType type)
	: _id(id), _parent(parent), _type(type)
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

ecs::Engine *ecs::Entity::getParent()
{
	return (_parent);
}

ecs::entityType ecs::Entity::getType()
{
	return _type;
}

bool ecs::Entity::hasComponent(const ecs::compType type)
{
	auto search = _components.find(type);
	if (search != _components.end()) {
		//debug
		//std::cout << "Entity " << _id << " has Component " << std::endl;
		return (true);
	}
	//debug
	std::cout << "Entity " << _id << ": Component not found" << std::endl;
 	return (false);
}

/*
** the 2 following functions should only be called after hasComponent
*/

ecs::Component *ecs::Entity::getComponent(const ecs::compType type)
{
	auto search = _components.find(type);
	if (search == _components.end()) {
		std::cout << _parent->_entities.size() << " entities\n";
		std::cout << "we are in entity " << _id << " \n";
		std::cerr << "no such component" << std::endl;
		return (NULL);
	}
	return ((search->second));
}

void ecs::Entity::updateComponent(ecs::compType type, ecs::Component &updated)
{
	_components[type] = &updated;
}

void ecs::Entity::addComponent(ecs::compType type, ecs::Component &cmp)
{
	_components[type] = &cmp;
}

void ecs::Entity::removeComponent(ecs::compType type)
{
	auto search = _components.find(type);
	if (search != _components.end()) {
		_components.erase(search);
	} else {
		std::cout << "Component not found, cannot be deleted" << std::endl;
	}
}
