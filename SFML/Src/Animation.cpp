//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#include <iostream>
#include "Animation.hpp"

Animation::Animation(SpriteCreator &creator, spriteType _type)
  : type(_type)
{
  switch (type) {
    case SHIP1:
    {
      type = SHIP_ANIM;
      spriteNb = 5;
      timer = sf::milliseconds(200);
      createAnim(sf::Vector2f(0, 0), sf::Vector2f(165 / 5, 85 / 5), sf::Vector2f(EXPLO_SIZE, EXPLO_SIZE), creator);
      break;
    }
    case SHIP2:
    {
      type = SHIP_ANIM;
      timer = sf::milliseconds(200);
      spriteNb = 5;
      createAnim(sf::Vector2f(165 / 5, 85 / 5), sf::Vector2f(165 / 5, 85 / 5), sf::Vector2f(EXPLO_SIZE, EXPLO_SIZE), creator);
      break;
    }
    case SHIP3:
    {
      type = SHIP_ANIM;
      spriteNb = 5;
      timer = sf::milliseconds(200);
      createAnim(sf::Vector2f(165 / 5 * 2, 85 / 5 * 2), sf::Vector2f(165 / 5, 85 / 5), sf::Vector2f(EXPLO_SIZE, EXPLO_SIZE), creator);
      break;
    }
    case SHIP4:
    {
      type = SHIP_ANIM;
      spriteNb = 5;
      timer = sf::milliseconds(200);
      createAnim(sf::Vector2f(165 / 5 * 3, 85 / 5 * 3), sf::Vector2f(165 / 5, 85 / 5), sf::Vector2f(EXPLO_SIZE, EXPLO_SIZE), creator);
      break;
    }
    default:
      haveAnim = false;
      break;
  }
}

Animation::~Animation()
{

}

void Animation::createAnim(sf::Vector2f posRect, sf::Vector2f pad, sf::Vector2f scale, SpriteCreator &creator)
{
  for (int i = 0; i < spriteNb; i++) {
    anim.push_back(creator.createSprite(type));
    anim[i].setTextureRect(sf::IntRect(posRect.x + i * pad.x, posRect.y, pad.x, pad.y));
    anim[i].setScale(scale);
  }
}

sf::Sprite Animation::getAnim()
{
  if (timer <= clock.getElapsedTime()) {
    animNb++;
    if (animNb == spriteNb)
      animNb = 0;
    clock.restart();
  }
  return anim[animNb];
}

bool Animation::getHaveAnim()
{
  return haveAnim;
}
