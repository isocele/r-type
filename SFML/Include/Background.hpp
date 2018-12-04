//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "SpriteCreator.hpp"

class Background {
public:
	Background(SpriteCreator &creator);
	~Background();
  void display(sf::RenderWindow &win);
private:
  std::vector<sf::Sprite> sprites;
	sf::Time timer = sf::milliseconds(5);
	sf::Clock clock;
	int randdir = 2;
};

#endif /*BACKGROUND_HPP */
