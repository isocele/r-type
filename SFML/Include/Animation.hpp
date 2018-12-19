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
	Animation(SpriteCreator &creator, spriteType type);
	~Animation();
	sf::Sprite getAnim();
	void createAnim(sf::Vector2f posRect, sf::Vector2f pad, sf::Vector2f scale, SpriteCreator &creator);
	bool getHaveAnim();
private:
	std::vector<sf::Sprite> anim;
	spriteType type;
	sf::Time timer = sf::milliseconds(100);
	sf::Clock clock;
	int animNb = 0;
	int spriteNb = 0;
	bool haveAnim = true;
};

#endif /* ANIMATION_HPP */
