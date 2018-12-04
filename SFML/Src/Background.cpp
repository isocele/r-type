//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#include "Background.hpp"

Background::Background(SpriteCreator &creator)
{
  sf::Sprite sprite;

  sprite = creator.createSprite(SPACE);
  sprite.setScale(sf::Vector2f(4.9, 4.9));
  sprites.push_back(sprite);
  sprite = creator.createSprite(ASTEROIDE);
  sprite.setPosition(sf::Vector2f(2000, 200));
  sprite.setOrigin(160.f, 160.f);
  sprites.push_back(sprite);
}

Background::~Background()
{

}

void Background::display(sf::RenderWindow &win)
{
  sf::Vector2f tmp;

  if (timer <= clock.getElapsedTime()) {
    int i = 0;
    for (auto& sprite : sprites) {
      win.draw(sprite);
      if (i == 0)
        sprite.move(-0.1, 0);
      else if (i == 1){
        sprite.rotate(0.2);
        sprite.move(-1, (float)randdir/5 - 1);
        tmp = sprite.getPosition();
        if (tmp.x < -1000){
          tmp.y = rand() % 1000;
          randdir = rand() % 10;
          sprite.setPosition(sf::Vector2f(2000, tmp.y));
        }
      }
      i++;
    }
    clock.restart();
  }
  else
  for (auto& sprite : sprites)
    win.draw(sprite);
}
