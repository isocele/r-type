/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Fight System
*/

#ifndef Fight_SYSTEM_HPP
#define Fight_SYSTEM_HPP

#include "System.hpp"
#include "PositionComponent.hpp"

namespace rtype {

	class Fight : public ecs::System {

	public:

		Fight(ecs::Engine *parent);
		int run(ecs::Entity &entity);

	private:

		void createMissile(int, int);

	};
}

#endif /* !Fight_SYSTEM_HPP */
