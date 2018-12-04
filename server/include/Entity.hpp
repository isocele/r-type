/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** ECS entity header
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <map>
#include <stdlib.h>
#include <vector>
#include <list>
#include <stdexcept>
#include "Utils.hpp"
#include "Component.hpp"

namespace ecs {

	class Engine;

	class Entity {

	friend class System;
	friend class Engine;
	friend class MoveSystem;

	public:

		Entity(int id, ecs::Engine *parent, entityType type);
		~Entity();
		int getID();
		Engine *getParent();
		ecs::entityType getType();
		bool hasComponent(const ecs::compType);
		Component *getComponent(const ecs::compType);
		void updateComponent(ecs::compType, ecs::Component &);
		void addComponent(ecs::compType, ecs::Component &);
		void removeComponent(ecs::compType);

	//protected:

		int _id;
		ecs::Engine *_parent;
		std::map<const ecs::compType, ecs::Component *> _components;
		ecs::entityType _type;
	};

}

#endif /* !ENTITY_HPP */
