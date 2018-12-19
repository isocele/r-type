//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#include "Controls.hpp"
#include <iostream>

Controls::Controls()
{

}

Controls::~Controls()
{

}

void Controls::reset()
{
  space = false;
  up = false;
  down = false;
  right = false;
  left = false;
}

void Controls::checkControls(Sound &sound)
{
  if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    spacereleased = true;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spacereleased == true)  {
    spacereleased = false;
    space = true;
    sound.stopTrack(SWPEW);
    sound.launchTrack(SWPEW);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    up = true;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    down = true;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    left = true;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    right = true;
}

bool Controls::getSpace()
{
  return space;
}

bool Controls::getUp()
{
  return up;
}

bool Controls::getDown()
{
  return down;
}

bool Controls::getLeft()
{
  return left;
}

bool Controls::getRight()
{
  return right;
}
