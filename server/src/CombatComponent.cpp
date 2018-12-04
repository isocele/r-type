/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Combat Component
*/

#include "CombatComponent.hpp"

ecs::Combat::Combat()
	: Component(ecs::COMBAT), _hp(1), _missiles(0), _damage(0)
{
//	std::cout << "Combat Component added" << std::endl;
}

ecs::Combat::Combat(int hp, int dmg)
	: Component(ecs::COMBAT), _hp(hp), _missiles(0), _damage(dmg)
{
}

unsigned int ecs::Combat::getHp()
{
	return _hp;
}

unsigned int ecs::Combat::getMissiles()
{
	return _missiles;
}

unsigned int ecs::Combat::getDamage()
{
	return _damage;
}

void ecs::Combat::setHp(unsigned int hp)
{
	_hp = hp;
}

void ecs::Combat::setMissiles(unsigned int missiles)
{
	_missiles = missiles;
}

void ecs::Combat::setDamage(unsigned int damage)
{
	_damage = damage;
}

void ecs::Combat::takeAHit()
{
	if (_hp > 0)
		_hp -= 1;
}

bool ecs::Combat::fireSuper()
{
	if (_missiles == 0) {
		std::cerr << "No missile available" << std::endl;
		return (false);
	}
	_missiles -= 1;
	std::cout << "Missile fired!" << std::endl;
	return (true);
}

bool ecs::Combat::fire()
{
	if (_damage == false)
		return (false);
	return (true);
}

ecs::Combat& ecs::Combat::operator=(Combat &other)
{
	_hp = other._hp;
	_missiles = other._missiles;
	_damage = other._damage;
	return (*this);
}
