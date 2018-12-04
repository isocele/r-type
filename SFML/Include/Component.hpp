//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "SpriteType.hpp"
#include "SpriteCreator.hpp"
#include "Animation.hpp"

class Component {
public:
	Component(spriteType type, int _num, sf::Vector2f newPos, SpriteCreator &creator);
	~Component();
	sf::Sprite getSprite();
	void setPos(sf::Vector2f newPos);
	sf::Vector2f getPos();
	spriteType getType();
	int getNum();
	void createAnim(sf::Vector2f pos, sf::Vector2f pad, sf::Vector2f scale, SpriteCreator &creator);
	void playAnimation();
	bool getAnimState();
	bool getPlayAnim();
private:
  sf::Sprite sprite;
	std::vector<sf::Sprite> anim;
  spriteType type;
  sf::Vector2f pos;
	int num;
	//Animation animation;
	sf::Time timer = sf::milliseconds(100);
	sf::Clock clock;
	int spriteNb = 0;
	int animNb = 0;
	animType typeAnim = NONE;
	bool playAnim = false;
	bool animState = true;
};

#endif /* COMPONENT_HPP */
