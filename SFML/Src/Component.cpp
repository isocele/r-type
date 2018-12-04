//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#include <iostream>
#include "Component.hpp"

Component::Component(spriteType _type, int _num, sf::Vector2f newPos, SpriteCreator &creator)
 : type(_type), pos(newPos), num(_num), typeAnim(static_cast<animType>(_type))
{
  sprite = creator.createSprite(type);
  sprite.setPosition(pos);
  if (type != MISSILE1 || type != MISSILE2) {
    typeAnim = EXPLO;
    spriteNb = 6;
    createAnim(sf::Vector2f(-3, 53), sf::Vector2f(200 / 6, 30), sf::Vector2f(EXPLO_SIZE, EXPLO_SIZE), creator);
  }
  else
    typeAnim = NONE;
}

Component::~Component()
{

}

void Component::createAnim(sf::Vector2f posRect, sf::Vector2f pad, sf::Vector2f scale, SpriteCreator &creator)
{
  for (int i = 0; i < spriteNb; i++) {
    anim.push_back(creator.createSprite(EXPLOSION));
    anim[i].setTextureRect(sf::IntRect(posRect.x + i * pad.x, posRect.y, pad.x, pad.y));
    anim[i].setScale(scale);
    anim[i].setPosition(pos);
  }
}

sf::Sprite Component::getSprite()
{
  if (typeAnim != NONE && playAnim) {
    if (timer <= clock.getElapsedTime()) {
      animNb++;
      if (animNb == spriteNb) {
        playAnim = false;
        animNb = 0;
        animState = false;
      }
      clock.restart();
    }
    return anim[animNb];
  }
  return sprite;
}

void Component::setPos(sf::Vector2f newPos)
{
  pos = newPos;
  sprite.setPosition(pos);
  for (int i = 0; i < spriteNb; i++)
    anim[i].setPosition(pos);
}

sf::Vector2f Component::getPos()
{
  return pos;
}

spriteType Component::getType()
{
  return type;
}

int Component::getNum()
{
  return num;
}

void Component::playAnimation()
{
  playAnim = true;
  animState = false;
}

bool Component::getAnimState()
{
  return animState;
}

bool Component::getPlayAnim()
{
  return playAnim;
}
