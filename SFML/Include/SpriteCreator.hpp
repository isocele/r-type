//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#ifndef SPRITE_CREATOR_HPP
#define SPRITE_CREATOR_HPP

#include <SFML/Graphics.hpp>
#include "SpriteType.hpp"

#define SHIP_SIZE 3.5
#define MISSILE_SIZE 2
#define EXPLO_SIZE 3.5
#define ENEMY_SIZE 2

class SpriteCreator {
public:
	SpriteCreator();
	~SpriteCreator();
	sf::Sprite createSprite(spriteType type);
	void createTexture(std::string img, spriteType type);
	void createCustomTexture(std::string img, spriteType type, sf::IntRect rect);
private:
	std::vector<std::unique_ptr<sf::Texture>> factory;
	int spriteNb = SPRITE_NB;
};

#endif /* SpriteCreator */
