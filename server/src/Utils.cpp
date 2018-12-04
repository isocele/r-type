/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Utils
*/

#include "Utils.hpp"

rtype::vector2::vector2()
	: x(0), y(0)
{
}

rtype::vector2::vector2(vector2 &cpy)
	: x(cpy.x), y(cpy.y)
{
}

rtype::vector2::vector2(int valX, int valY)
	: x(valX), y(valY)
{
}

rtype::vector2 &rtype::vector2::operator+=(vector2 &other)
{
	this->x = this->x + other.x;
	this->y = this->y + other.y;
	return (*this);
}

rtype::vector2 &rtype::vector2::operator-=(vector2 &other)
{
	this->x = this->x - other.x;
	this->y = this->y - other.y;
	return (*this);
}

rtype::vector2 &rtype::vector2::operator=(vector2 &other)
{
	this->x = other.x;
	this->y = other.y;
	return (*this);
}

bool rtype::vector2::operator==(vector2 &other)
{
	if (this->x == other.x && this->y == other.y)
		return (true);
	return (false);
}

bool rtype::vector2::operator!=(vector2 &other)
{
	if (this->x != other.x || this->y != other.y)
		return (true);
	return (false);
}
