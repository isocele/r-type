/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Combat Component
*/

#ifndef COMBAT_COMPONENT_
#define COMBAT_COMPONENT_

#include "Component.hpp"

namespace ecs {

	class Combat : public Component {

	public:

		Combat();
		Combat(int hp, int damage);

		unsigned int getHp();
		unsigned int getMissiles();
		unsigned int getDamage();
		void setHp(unsigned int hp);
		void setMissiles(unsigned int missiles);
		void setDamage(unsigned int damage);

		//actions
		void takeAHit();
		bool fire();
		bool fireSuper();

		Combat& operator=(Combat &other);

	private:

		unsigned int _hp;
		unsigned int _missiles;
		unsigned int _damage;
	};

}

#endif /* !COMBAT_COMPONENT_ */
