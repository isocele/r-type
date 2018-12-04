/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** System header
*/

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <iostream>
#include "Entity.hpp"
#include "Utils.hpp"

namespace ecs {

	class Engine;

	class System
	{

	friend class Entity;
	friend class Engine;

	public:
		System(ecs::sysType, Engine *parent);
		virtual ~System() = default;
		ecs::sysType getType();
		ecs::Engine *getParent();
		virtual int run(Entity &entity);

	protected:
		ecs::sysType _type;
		Engine *_parent;
	};

}

#endif /* SYSTEM_HPP */
