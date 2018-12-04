/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** ECS Game Engine
*/

#include <stdexcept>
#include "MoveSystem.hpp"
#include "FightSystem.hpp"
#include "GameEngine.hpp"

/*
** Game-specific implementation of ECS engine update
*/

void ecs::Engine::implementUpdate()
{
	if (_firstUpdate) {
		if (!hasSystem(ecs::MOVE) || !hasSystem(ecs::FIGHT))
			throw("ERROR: missing critical ECS Systems");
		_firstUpdate = false;
	}

	auto ent = _entities.begin();
	auto moveSystem = dynamic_cast<rtype::Move &>(getSystem(ecs::MOVE));
	auto fightSystem = dynamic_cast<rtype::Fight &>(getSystem(ecs::FIGHT));

	for (ent ++ ; ent != _entities.end();) {
		if (ent->hasComponent(ecs::POSITION) && (ent->getType() == E_MISSILE
			|| ent->getType() == P_MISSILE || ent->getType() == ENEMY))
			moveSystem.run(*ent);
		if (ent->getType() == ecs::ENEMY)
			fightSystem.run(*ent);
	}

	// add monster spawning
	// add score handling

}
