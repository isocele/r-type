//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#include "Sound.hpp"
#include <iostream>

Sound::Sound()
{
  for (int i = 0; i < nb_track; i++) {
    std::unique_ptr<sf::Music> musicPtr(new sf::Music);
    _music.push_back(std::move(musicPtr));
  }
  createSound("SFML/assets/pkm.ogg", PKM);
  createSound("SFML/assets/welcome.ogg", WELCOME);
  createSound("SFML/assets/starwarspew.ogg", SWPEW);
  createSound("SFML/assets/Explosion+1.ogg", BOMB);
}

Sound::~Sound()
{

}

void Sound::createSound(std::string path, TRACK type)
{
	if (!_music[type]->openFromFile(path))
  {
    std::cout << "kk" << '\n';
        std::cout << "Error loading Music" << std::endl;
      }
}

void Sound::launchTrack(TRACK type)
{
  _music[type]->play();
}

void Sound::stopTrack(TRACK type)
{
  _music[type]->stop();
}
