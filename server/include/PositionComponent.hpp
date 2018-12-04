/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Position Component
*/

#ifndef POSITION_COMPONENT_
#define POSITION_COMPONENT_

#include "Component.hpp"
#include "Utils.hpp"

namespace ecs {

	class Position : public Component {

	public:

		Position();
		Position(int x, int y, int angle);

		rtype::vector2 &getPos();
		int getX();
		int getY();
		int getAngle();
		float getSpeed();
		bool isAutonomous();

		void setPos(int x, int y);
		void setPos(rtype::vector2 pos);
		void setAngle(int angle);
		void setSpeed(float speed);
		void setAutonomous();
		void setAutonomous(bool value);

		Position& operator+=(Position &other);
		Position& operator-=(Position &other);
		Position& operator=(Position &other);
		bool operator==(Position &b);
		bool operator!=(Position &b);

	private:

		rtype::vector2 _pos;
		int _angle;
		float _speed;
		bool _auto;

	};

}

#endif /* !POSITION_COMPONENT_ */
