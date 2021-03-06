/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** ECS Game Engine header
*/

#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include "System.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

namespace ecs {

	class Engine {

	friend class System;
	friend class MoveSystem;
	friend class Entity;

	public:

		Engine();
		~Engine() = default;

		//Entity management
		Entity &newEntity();
		Entity &newEntity(entityType);
		Entity &getEntity(int id);
		Entity &addEntity(Entity &ent);
		bool killEntity(int id);
		bool killEntity(Entity &ent);
		std::vector<ecs::Entity> &getEntities();

		//System Management
		System &getSystem(ecs::sysType);
		System &newSystem(ecs::sysType type);
		System &newSystem(ecs::sysType type, System&);
		bool hasSystem(ecs::sysType type);

		int genID();

	private:

		std::vector<ecs::Entity> _entities;
		std::vector<ecs::System> _systems;
		int _idCounter;
		unsigned int _sysCounter;
		bool _firstUpdate;

		//no exterior class should be able to kill systems ?
		bool killSystem(int id);

	};

}

#endif /* !GAME_ENGINE_HPP */
