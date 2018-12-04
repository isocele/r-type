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
	if (entity.hasComponent(ecs::POSITION) && entity.hasComponent(ecs::GRAPHICAL)) {
		auto pos = new ecs::Position;
		auto gr = new ecs::Graphical;
		pos = dynamic_cast<ecs::Position *>(entity.getComponent(ecs::POSITION));
		gr = dynamic_cast<ecs::Graphical *>(entity.getComponent(ecs::GRAPHICAL));
		if (pos->isAutonomous() == false)
			return (1);

		// add monster movement AI;

		gr->setSpritePos(pos->getPos());
		entity.updateComponent(ecs::POSITION, *pos);
		checkForCollisions(entity);
		return (0);
	}
	return (-1);
}

/*
** for players: specify position to add
*/

int rtype::Move::run(ecs::Entity &entity, ecs::Position &add)
{
	if (entity.hasComponent(ecs::POSITION) && entity.hasComponent(ecs::GRAPHICAL)) {
		auto pos = new ecs::Position;
		auto gr = new ecs::Graphical;
		pos = dynamic_cast<ecs::Position *>(entity.getComponent(ecs::POSITION));
		gr = dynamic_cast<ecs::Graphical *>(entity.getComponent(ecs::GRAPHICAL));
		*pos += add;
		gr->setSpritePos(pos->getPos());
		entity.updateComponent(ecs::POSITION, *pos);
		entity.updateComponent(ecs::GRAPHICAL, *gr);
		checkForCollisions(entity);
		return (0);
	}
	return (-1);
}

/*
** When moving any entity, check for collisions
** with other entities
*/

bool rtype::Move::checkForCollisions(ecs::Entity &entity)
{
	auto tmp = new ecs::Position;
	auto pos = dynamic_cast<ecs::Position *>(entity.getComponent(ecs::POSITION));

	std::vector<ecs::Entity> entities = entity._parent->_entities;
	for (auto& ent : entities) {
		tmp = dynamic_cast<ecs::Position *>(ent.getComponent(ecs::POSITION));
		if (ent._id != entity._id && tmp != NULL) {
			if (tmp == pos && collide(entity, ent) == true)
				 return (isDead(entity));
		}
	}
	return (false);
}

/*
** if 2 entities of the same type collide, do nothing
** if a player hits an enemy, a missile or wall, remove a life
** if an enemy hit a missile, kill him
** return false if collision had consequences
*/

bool rtype::Move::collide(ecs::Entity &moved, ecs::Entity &hit)
{
	if (moved._type == hit._type)
		return (false);
	if (moved._type == ecs::PLAYER && hit._type != ecs::P_MISSILE)
		hitEntity(moved);
	else if (hit._type == ecs::PLAYER && hit._type != ecs::P_MISSILE) {
		hitEntity(moved);
		isDead(hit);
	} else if (moved._type == ecs::ENEMY && hit._type != ecs::E_MISSILE)
		hitEntity(moved);
	else if (hit._type == ecs::ENEMY && moved._type != ecs::E_MISSILE) {
		hitEntity(moved);
		isDead(hit);
	} else if ((moved._type == ecs::P_MISSILE || moved._type == ecs::E_MISSILE) && hit._type == ecs::WALL)
		hitEntity(moved);
	else if ((moved._type == ecs::P_MISSILE || moved._type == ecs::E_MISSILE) && hit._type == ecs::STATIC) {
		hitEntity(moved);
		isDead(hit);
	}
	return (true);
}

/*
** When hitting unfriendlty entity:
** have the hit entity take damage
*/

void rtype::Move::hitEntity(ecs::Entity &hit)
{
	auto CombatStats = dynamic_cast<ecs::Combat *>(hit.getComponent(ecs::COMBAT));

	if (CombatStats == NULL) {
		std::cerr << "Entity hit has no HP counter" << std::endl;
		return ;
	}
	CombatStats->takeAHit();
	std::cout << "Entity " << hit._id << " took a hit !" << std::endl;
}

/*
** Check if damaged entity died
** having 1 life at default, it usually does except
** for powered-up players or enemy bosses
*/

bool rtype::Move::isDead(ecs::Entity &hit)
{
	auto CombatStats = dynamic_cast<ecs::Combat *>(hit.getComponent(ecs::COMBAT));

	if (CombatStats == NULL)
		return (false);
	if (CombatStats->getHp() == 0) {
		std::cout << "Entity " << hit._id << " was destroyed / died !" << std::endl;
		hit._parent->killEntity(hit._id);
		return (true);
	}
	return (false);
}
