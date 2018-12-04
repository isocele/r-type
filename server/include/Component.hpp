/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Component header
*/

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <vector>
#include <list>
#include <map>
#include <iostream>
#include "Utils.hpp"

namespace ecs {

	class Component
	{

	public:
		Component();
		Component(ecs::compType type);
		virtual ~Component() = default;

	protected:
		ecs::compType _type;
	};

}
#endif /* COMPONENT_HPP */
