/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Fight System
*/

#include "FightSystem.hpp"
#include "PositionComponent.hpp"
#include "GraphicalComponent.hpp"
#include "CombatComponent.hpp"
#include "GameEngine.hpp"

rtype::Fight::Fight(ecs::Engine *parent)
	: System(ecs::FIGHT, parent)
{
}

/*
** basically, fire a missile if available
*/

void rtype::Fight::createMissile(int x, int y)
{
	ecs::Entity m(_parent->genID(), _parent, ecs::P_MISSILE);
	int offset = 50;
	x += offset;
	m.addComponent(new ecs::Position(x, y, 0, 2, true));
	m.addComponent(new ecs::Combat(1, 1));
	m.addComponent(new ecs::Graphical(ecs::S_MISSILE_P, x, y));
	_parent->addEntity(m);
}

int rtype::Fight::run(ecs::Entity &entity)
{
	if (entity.hasComponent(ecs::COMBAT) && entity.hasComponent(ecs::POSITION)) {

		auto combatStats = dynamic_cast<ecs::Combat *>(entity.getComponent(ecs::COMBAT));
		auto pos = dynamic_cast<ecs::Position *>(entity.getComponent(ecs::POSITION));

		if (combatStats->fire() == true) {
			createMissile(pos->getX(), pos->getY());
		}
	}
	return (0);
}
