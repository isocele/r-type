//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "SpriteCreator.hpp"


class Animation {
public:
	Animation(SpriteCreator &creator, int spriteNb, sf::Vector2f pos, sf::Vector2f pad);
	~Animation();
  void createAnim();
	sf::Sprite getAnimAt(int pos);
private:
	std::vector<sf::Sprite> anim;
};

#endif /* ANIMATION_HPP */
