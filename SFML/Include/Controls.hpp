//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <SFML/Graphics.hpp>

class Controls  {
public:
	Controls ();
	~Controls ();
  void reset();
  void checkControls();
  bool getSpace();
  bool getUp();
  bool getDown();
  bool getLeft();
  bool getRight();
private:
	bool escape = false;
	bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
  bool space = false;
	bool spacereleased = true;
};

#endif /* CONTROLS _HPP */
