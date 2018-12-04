/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Graphical Component
*/

#ifndef GRAPHICAL_COMPONENT_
#define GRAPHICAL_COMPONENT_

#include "Component.hpp"

namespace ecs {

	class Graphical : public Component {

	public:

		Graphical();
		Graphical(spriteType, int, int);

		void setSpritePos(int valX, int valY);
		void setSpritePos(rtype::vector2 pos);
		void setSpriteType(ecs::spriteType type);
		rtype::vector2 &getSpritePos();
		ecs::spriteType getSpriteType();

		Graphical& operator=(Graphical &other);

	private:

		rtype::vector2 _pos;
		spriteType _sprite;
	};

}

#endif /* !GRAPHICAL_COMPONENT_ */
