/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Move System
*/

#include "MoveSystem.hpp"
#include "GameEngine.hpp"

rtype::Move::Move(ecs::Engine *parent)
	: System(ecs::MOVE, parent)
{
}

/*
** default movement function: for enemies & missiles
*/

int rtype::Move::run(ecs::Entity &entity)
{
	int ret = 0;

	if (entity.hasComponent(ecs::POSITION) && entity.hasComponent(ecs::GRAPHICAL)) {
		auto pos = dynamic_cast<ecs::Position *>(entity.getComponent(ecs::POSITION));
		auto gr = dynamic_cast<ecs::Graphical *>(entity.getComponent(ecs::GRAPHICAL));
		if (pos->isAutonomous() == false) {
			std::cout << "no autonoumous movement\n";
			return (1);
		}
		pos->setX(pos->getX() + pos->getSpeed());
		// add monster movement AI;
		gr->setSpritePos(pos->getPos());
		ret = checkForCollisions(entity);
		if (ret >= 0)
			return ret;
		if ((pos->getSpeed() > 0) && (pos->getX() > LENGTH))
			_parent->killEntity(entity);
		if ((pos->getSpeed() < 0) && (pos->getX() < -10))
			_parent->killEntity(entity);
		return 0;
	}
	return -1;
}

/*
** for players: specify position to add
*/

int rtype::Move::run(ecs::Entity &entity, ecs::Position &add)
{
	if (entity.hasComponent(ecs::POSITION) && entity.hasComponent(ecs::GRAPHICAL)) {
		auto pos = dynamic_cast<ecs::Position *>(entity.getComponent(ecs::POSITION));
		auto gr = dynamic_cast<ecs::Graphical *>(entity.getComponent(ecs::GRAPHICAL));
		*pos += add;
		gr->setSpritePos(pos->getPos());
		return (checkForCollisions(entity));
	}
	return -1;
}

/*
** When moving any entity, check for collisions
** with other entities
*/

int rtype::Move::checkForCollisions(ecs::Entity &entity)
{
	auto pos = dynamic_cast<ecs::Position *>(entity.getComponent(ecs::POSITION));
	int x = pos->getX();
	int y = pos->getY();

	std::vector<ecs::Entity> entities = _parent->getEntities();
	for (auto& ent : entities) {
		auto tmp = dynamic_cast<ecs::Position *>(ent.getComponent(ecs::POSITION));
		if (ent.getID() != entity.getID() && (abs(x - tmp->getX()) < 50 && abs(y - tmp->getY()) < 50)) {
			return (collide(entity, ent));
		}
	}
	return (0);
}

/*
** if 2 entities of the same type collide, do nothing
** if a player hits an enemy, a missile or wall, remove a life
** if an enemy hit a missile, kill him
** return false if collision had consequences
*/

int rtype::Move::collide(ecs::Entity &moved, ecs::Entity &hit)
{
	int ret = 0;
	if (moved.getType() == hit.getType())
		return ret;
	else if (moved.getType() == ecs::PLAYER && hit.getType() == ecs::ENEMY) {
		ret = moved.getIndex();
		_parent->killEntity(moved);
	} else if (moved.getType() == ecs::ENEMY && hit.getType() == ecs::PLAYER) {
		ret = hit.getIndex();
		_parent->killEntity(hit);
	} else if (hit.getType() == ecs::ENEMY && moved.getType() == ecs::P_MISSILE) {
		_parent->killEntity(hit);
		_parent->killEntity(moved);
	} else if (hit.getType() == ecs::P_MISSILE && moved.getType() == ecs::ENEMY) {
		_parent->killEntity(hit);
		_parent->killEntity(moved);
	} else if (hit.getType() == ecs::E_MISSILE && moved.getType() == ecs::PLAYER) {
		ret = moved.getIndex();
		_parent->killEntity(hit);
		_parent->killEntity(moved);
	} else if (hit.getType() == ecs::PLAYER && moved.getType() == ecs::E_MISSILE) {
		ret = hit.getIndex();
		_parent->killEntity(hit);
		_parent->killEntity(moved);
	} else
		return (-1);
	return ret;
}

/*
** addScore to all players when a friendly missile
** hits an enemy or an enemy missile
*/

void rtype::Move::addScore(int val)
{
	auto entities = _parent->getEntities();

	for (size_t i = 0; i < entities.size(); i++) {
		if (entities[i].getType() == ecs::PLAYER &&
		entities[i].hasComponent(ecs::SCORE)) {
			auto score = dynamic_cast<ecs::Score *>(entities[i].getComponent(ecs::SCORE));
			score += val;
		}
	}
}

/*
** When hitting unfriendlty entity:
** have the hit entity take damage
*/

void rtype::Move::hitEntity(ecs::Entity &hit)
{
	if (!hit.hasComponent(ecs::COMBAT)) {
		std::cerr << "Entity hit has no HP counter" << std::endl;
		return ;
	}
	auto CombatStats = dynamic_cast<ecs::Combat *>(hit.getComponent(ecs::COMBAT));
	CombatStats->takeAHit();
}

/*
** Check if damaged entity died
** having 1 life at default, it usually does except
** for powered-up players or enemy bosses
*/

bool rtype::Move::isDead(ecs::Entity &hit)
{
	if (!hit.hasComponent(ecs::COMBAT))
		return (false);
	auto CombatStats = dynamic_cast<ecs::Combat *>(hit.getComponent(ecs::COMBAT));
	if (CombatStats->getHp() == 0) {
		std::cout << "Entity " << hit.getID() << " was destroyed / died !" << std::endl;
		_parent->killEntity(hit);
		return (true);
	}
	return (false);
}
