/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** ECS Component
*/

#include "Component.hpp"

ecs::Component::Component()
	:_type(ecs::DEFAULT)
{
}

ecs::Component::Component(ecs::compType type)
	: _type(type)
{
}
