/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Score Component
*/

#include "ScoreComponent.hpp"

ecs::Score::Score()
	: Component(ecs::SCORE), _score(0)
{
}

int ecs::Score::getScore()
{
	return _score;
}

void ecs::Score::setScore(int s)
{
	_score = s;
}

ecs::Score& ecs::Score::operator=(Score &other)
{
	_score = other._score;
	return (*this);
}

ecs::Score& ecs::Score::operator+=(Score &other)
{
	_score += other._score;
	return (*this);
}

ecs::Score& ecs::Score::operator-=(Score &other)
{
	_score -= other._score;
	return (*this);
}

ecs::Score& ecs::Score::operator+=(int s)
{
	_score += s;
	return (*this);
}

ecs::Score& ecs::Score::operator-=(int s)
{
	_score -= s;
	return (*this);
}
