/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** ECS System
*/

#include "System.hpp"

ecs::System::System(ecs::sysType type, Engine *parent)
	: _type(type), _parent(parent)
{
}

ecs::sysType ecs::System::getType()
{
	return _type;
}

ecs::Engine *ecs::System::getParent()
{
	return _parent;
}

int ecs::System::run(Entity &entity)
{
	(void)(entity);
	return (0);
}
