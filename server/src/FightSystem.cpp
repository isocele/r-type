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
	std::cout << "missile has id " << m.getID() << std::endl;
	int offset = 50;
	x += offset;
	y += offset;

	m.addComponent(ecs::POSITION, dynamic_cast<ecs::Component &>(*(new ecs::Position(x, y, 0))));
	m.addComponent(ecs::COMBAT, dynamic_cast<ecs::Component &>(*(new ecs::Combat(1, 1))));
	m.addComponent(ecs::GRAPHICAL, dynamic_cast<ecs::Component &>(*(new ecs::Graphical(ecs::S_MISSILE_P, x, y))));
	int id = _parent->addEntity(m).getID();
	std::cout << "New player missile entity created with ID " << id << std::endl;
}

int rtype::Fight::run(ecs::Entity &entity)
{
	if (entity.hasComponent(ecs::COMBAT)) {
		auto combatStats = new ecs::Combat;
		combatStats = dynamic_cast<ecs::Combat *>(entity.getComponent(ecs::COMBAT));
		if (combatStats->fire() == true) {
			//auto playerPos = dynamic_cast<ecs::Position *>(entity.getComponent(ecs::POSITION));
			//auto gr = dynamic_cast<ecs::Graphical *>(entity.getComponent(ecs::GRAPHICAL));
			createMissile(200, 200);//playerPos->getX(), playerPos->getY());
		}
	}
	return (0);
}
