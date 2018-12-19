/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Score Component
*/

#ifndef SCORE_COMPONENT_
#define SCORE_COMPONENT_

#include "Component.hpp"
#include "Utils.hpp"

namespace ecs {

	class Score : public Component {

	public:

		Score();

		void setScore(int s);
		int getScore();

		Score& operator=(Score &other);
		Score& operator+=(Score &other);
		Score& operator-=(Score &other);
		Score& operator+=(int);
		Score& operator-=(int);

	private:

		int _score;

	};

}

#endif /* !Score_COMPONENT_ */
