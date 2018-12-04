/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** graphical Component
*/

#include "GraphicalComponent.hpp"

ecs::Graphical::Graphical()
	: Component(ecs::GRAPHICAL)
{
//	std::cout << "Graphical Component added" << std::endl;
}

ecs::Graphical::Graphical(spriteType type, int x, int y)
	: Component(ecs::GRAPHICAL), _sprite(type)
{
	_pos.x = x;
	_pos.y = y;
}

void ecs::Graphical::setSpriteType(ecs::spriteType sprite)
{
	_sprite = sprite;
}

void ecs::Graphical::setSpritePos(rtype::vector2 pos)
{
	_pos = pos;
}

void ecs::Graphical::setSpritePos(int valX, int valY)
{
	_pos.x = valX;
	_pos.y = valY;
}

rtype::vector2 &ecs::Graphical::getSpritePos()
{
	return _pos;
}

ecs::spriteType ecs::Graphical::getSpriteType()
{
	return _sprite;
}

ecs::Graphical& ecs::Graphical::operator=(Graphical &other)
{
	_pos = other._pos;
	_sprite = other._sprite;
	return (*this);
}
