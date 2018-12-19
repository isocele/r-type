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
  std::cout << "oui" << '\n';
  createSound("SFML/assets/pkm.ogg", PKM);
  createSound("SFML/assets/welcome.ogg", WELCOME);
  createSound("SFML/assets/starwarspew.wav", SWPEW);
  createSound("SFML/assets/Explosion+1.ogg", BOMB);

  // for (int i = 0; i < nb_sound; i++) {
  //   std::unique_ptr<sf::SoundBuffer> bufferPtr(new sf::SoundBuffer);
  //   _buffer.push_back(std::move(bufferPtr));
  // }
  // if (!_buffer[0].loadFromFile("SFML/assets/starwarspew.ogg"))
  //   std::cout << "file not found" << '\n';
  // if (!_buffer[0].loadFromFile("SFML/assets/Explosion+1.ogg"))
  //   std::cout << "file not found" << '\n';
  // for (int i = 0; i < nb_sound; i++) {
  //   std::unique_ptr<sf::Sound> soundPtr(new sf::Sound);
  //   _sound.push_back(std::move(soundPtr));
  //   _sound.back().setBuffer(_buffer[i]);
  // }
}

Sound::~Sound()
{

}

void Sound::createSound(std::string path, TRACK type)
{
	if (!_music[type]->openFromFile(path))
  {
        std::cout << "Error loading Music" << std::endl;
      }
}

void Sound::launchTrack(TRACK type)
{
  // std::cout << "kk" << '\n';
  // _music[type]->setPlayingOffset(sf::seconds(0.2));
  _music[type]->play();
}

void Sound::stopTrack(TRACK type)
{
  _music[type]->stop();
}

// void Sound::launchSound(SOUND type)
// {
//   std::cout << "kk" << '\n';
//   _sound[type]->play();
// }
//
// void Sound::stopSound(SOUND type)
// {
//   _sound[type]->stop();
// }
