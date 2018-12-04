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

class Sound  {
public:
	Sound ();
	~Sound ();
  void reset();
  void checkSound();
  void launchTrack(TRACK value);
	void stopTrack(TRACK value);
	void createSound(std::string path, TRACK type);
private:
	sf::Music PKMtrack;
	sf::Music WELCOMEtrack;
	std::vector<std::unique_ptr<sf::Music>> _music;
	int nb_track = NB_TRACK;
};

#endif /* Sound _HPP */
