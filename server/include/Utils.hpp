/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** ECS Compnents (enum)
*/

#ifndef COMPONENT_TYPES_H_
#define COMPONENT_TYPES_H_

/*
** For easier operations on
** PositionComponent & GraphicalComponent
*/

namespace rtype {

	class vector2 {

	public:

		vector2();
		vector2(vector2 &cpy);
		vector2(int valX, int valY);
		~vector2() = default;
		int x;
		int y;
		vector2 &operator+=(vector2 &other);
		vector2 &operator-=(vector2 &other);
		vector2 &operator=(vector2 &other);
		bool operator==(vector2 &other);
		bool operator!=(vector2 &other);
	};

}

/*
** Types of Entities, Systems & Sprites
** for easier Management
*/

namespace ecs {

	enum entityType {
		STATIC = 0,
		PLAYER = 1,
		ENEMY = 2,
		P_MISSILE = 3,
		E_MISSILE = 4,
		WALL = 5
	};

	enum sysType {
		MOVE = 0,
		FIGHT = 1,
		COLLISION = 2,
		NONE = 3
	};

	enum compType {
		POSITION = 0,
		GRAPHICAL = 1,
		COMBAT = 2,
		SCORE = 3,
		DEFAULT = 4
	};

	enum spriteType {
		S_SHIP1 = 0,
		S_SHIP2 = 1,
		S_SHIP3 = 2,
		S_SHIP4 = 3,
		S_MISSILE_P = 4,
		S_MISSILE_E = 5,
		S_MONSTER = 6,
		S_BGD = 7,
		S_SPACE = 8,
		S_TILE = 9
	};

}

#define LENGTH 1440 //1930
#define HEIGHT 900 //1090

#endif /* !COMPONENT_TYPES_H_ */
