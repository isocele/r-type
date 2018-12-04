//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#include "SpriteCreator.hpp"
#include <iostream>

SpriteCreator::SpriteCreator()
{
	for (int i = 0; i < spriteNb; i++) {
		std::unique_ptr<sf::Texture> texturePtr(new sf::Texture);
		factory.push_back(std::move(texturePtr));
	}
	// createCustomTexture("SFML/assets/ships.gif", SHIP, sf::IntRect(0, 20, 0, 10));
	createTexture("SFML/assets/ship1.png", SHIP1);
	createTexture("SFML/assets/ship2.png", SHIP2);
	createTexture("SFML/assets/ship3.png", SHIP3);
	createTexture("SFML/assets/ship4.png", SHIP4);
	createTexture("SFML/assets/bulletBlue.png", MISSILE1);
	createTexture("SFML/assets/bulletRoundYellow.png", MISSILE2);
	createTexture("SFML/assets/enemyRobot1.png", ENEMY1);
	createTexture("SFML/assets/enemyRobot2.png", ENEMY2);
	createTexture("SFML/assets/spaceBackground.png", SPACE);
	createTexture("SFML/assets/sprites/Button.png", BUTTON);
	createTexture("SFML/assets/sprites/r-typesheet43.gif", EXPLOSION);//, sf::IntRect(42, 37, 32, 32));
	createTexture("SFML/assets/asteroide.png", ASTEROIDE);
	createTexture("SFML/assets/Title.png", TITLE);
	createTexture("SFML/assets/readyOK.png", READY);
	createTexture("SFML/assets/cross.png", CROSS);
}

SpriteCreator::~SpriteCreator()
{

}

sf::Sprite SpriteCreator::createSprite(spriteType type)
{
	sf::Sprite sprite;

	sprite.setTexture(*factory[type]);
	if (type == SHIP1 || type == SHIP2 || type == SHIP3 || type == SHIP4)
		sprite.setScale(sf::Vector2f(SHIP_SIZE, SHIP_SIZE));
	else if (type == MISSILE1 || type == MISSILE2)
		sprite.setScale(sf::Vector2f(MISSILE_SIZE, MISSILE_SIZE));
	else if (type == ENEMY1 || type == ENEMY2)
		sprite.setScale(sf::Vector2f(ENEMY_SIZE, ENEMY_SIZE));
	return sprite;
}

void SpriteCreator::createTexture(std::string img, spriteType type)
{
	if (!factory[type]->loadFromFile(img))
          std::cout << "Error loading Texture" << std::endl;
}

void SpriteCreator::createCustomTexture(std::string img, spriteType type, sf::IntRect rect)
{
	if (!factory[type]->loadFromFile(img, rect))
          std::cout << "Error loading Texture" << std::endl;
}
