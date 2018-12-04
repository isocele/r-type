/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Position Component
*/

#include "PositionComponent.hpp"

ecs::Position::Position()
	: Component(ecs::POSITION), _angle(0), _speed(10), _auto(false)
{
//	std::cout << "Position Component added" << std::endl;
}

ecs::Position::Position(int x, int y, int angle)
	: Component(ecs::POSITION), _angle(angle), _speed(10), _auto(false)
{
	_pos.x = x;
	_pos.y = y;
}

int ecs::Position::getAngle()
{
	return _angle;
}

int ecs::Position::getX()
{
	return(_pos.x);
}

int ecs::Position::getY()
{
	return(_pos.y);
}

void ecs::Position::setAngle(int angle)
{
	_angle = angle;
}

void ecs::Position::setPos(rtype::vector2 pos)
{
	std::cout << "ok" << '\n';
	_pos.x = pos.x;
	_pos.y = pos.y;
}

void ecs::Position::setPos(int valX, int valY)
{
	std::cout << "oki" << '\n';
	_pos.x = valX;
	_pos.y = valY;
}

rtype::vector2 &ecs::Position::getPos()
{
	return _pos;
}

bool ecs::Position::isAutonomous()
{
	return _auto;
}

/*
** add autonoumous movement to Entity
** (for missiles and enemies)
*/

void ecs::Position::setAutonomous()
{
	_auto = true;
	_speed = 1;
}

void ecs::Position::setAutonomous(bool value)
{
	_auto = value;
}

float ecs::Position::getSpeed()
{
	return _speed;
}

void ecs::Position::setSpeed(float speed)
{
	_speed = speed;
}

/*
** used to update position;
** adds dir, pos and speed
** -> to be used for power-ups
*/

ecs::Position& ecs::Position::operator+=(Position &other)
{
	int temp = _angle + other._angle;
	if (temp > 360 || temp < 0)
		_angle = temp % 360;
	else
		_angle = temp;
	_pos += other._pos;
	_speed += other._speed;
	return (*this);
}

ecs::Position& ecs::Position::operator-=(Position &other)
{
	int temp = _angle - other._angle;
	if (temp > 360 || temp < 0)
		_angle = temp % 360;
	else
		_angle = temp;
	_pos -= other._pos;
	_speed -= other._speed;
	return (*this);
}

ecs::Position& ecs::Position::operator=(Position &other)
{
	_auto = other._auto;
	_angle = other._angle;
	_pos = other._pos;
	_speed = other._speed;
	return (*this);
}

bool ecs::Position::operator==(Position &b)
{
	if (this->_pos == b._pos)
		return (true);
	return (false);
}

bool ecs::Position::operator!=(Position &b)
{
	if (this->_pos != b._pos)
		return (true);
	return (false);
}
