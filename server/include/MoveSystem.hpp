/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Move System
*/

#ifndef MOVE_SYSTEM_HPP
#define MOVE_SYSTEM_HPP

#include "System.hpp"
#include "PositionComponent.hpp"
#include "CombatComponent.hpp"
#include "GraphicalComponent.hpp"

/*
** System managing the movements & collisions of entites
*/

namespace rtype {

	class Move : public ecs::System {

	public:

		Move(ecs::Engine *parent);
		int run(ecs::Entity &entity);
		int run(ecs::Entity &entity, ecs::Position &add);

	private:

		bool checkForCollisions(ecs::Entity &entity);
		bool collide(ecs::Entity &moved, ecs::Entity&hit);
		void hitEntity(ecs::Entity &hit);
		bool isDead(ecs::Entity &hit);

	};
}

#endif /* !MOVE_SYSTEM_HPP */
