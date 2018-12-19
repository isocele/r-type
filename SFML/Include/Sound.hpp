//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#ifndef Sound_HPP
#define Sound_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum TRACK {
	PKM,
	WELCOME,
	SWPEW,
  BOMB,

	NB_TRACK,
 };

//  enum SOUND {
//  SWPEW,
//  BOMB,
//
//  NB_SOUND,
// };

class Sound  {
public:
	Sound ();
	~Sound ();
  void reset();
  void checkSound();
  void launchTrack(TRACK value);
	void stopTrack(TRACK value);
	// void launchSound(SOUND type);
	// void stopSound(SOUND type);
	void createSound(std::string path, TRACK type);
private:
	std::vector<sf::SoundBuffer> _buffer;
	std::vector<sf::Sound> _sound;
	std::vector<std::unique_ptr<sf::Music>> _music;
	int nb_track = NB_TRACK;
	// int nb_sound = NB_SOUND;
};

#endif /* Sound _HPP */
