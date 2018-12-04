//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#include <iostream>
#include "Animation.hpp"

Animation::Animation(SpriteCreator &creator, int spriteNb, sf::Vector2f pos, sf::Vector2f pad)
{
  for (int i = 0; i < spriteNb; i++) {
    anim.push_back(creator.createSprite(EXPLOSION));
    anim[i].setTextureRect(sf::IntRect(pos.x + i * pad.x, pos.y, pad.x, pad.y));
    anim[i].setScale(sf::Vector2f(5, 5));
    anim[i].setPosition(pos);
  }
}

Animation::~Animation()
{

}

sf::Sprite Animation::getAnimAt(int pos)
{
  return anim[pos];
}
