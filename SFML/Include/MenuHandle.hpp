/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Menu handler
*/

#ifndef MENU_HANDLE_HPP
#define MENU_HANDLE_HPP

#include "SpriteCreator.hpp"
#include <SFML/Graphics.hpp>

#include <iostream>

#define MARGIN 100
#define PADDING 200
#define LPADDING 80
#define MIDSCREEN 400
#define CENTER 20
#define MAX_PLAYER 4

enum LauncherButton {
  SOLO,
  MULTI,
  QUIT,

  BUTTON_NB,
};

enum LobbyButton {
  BACK,
  READYON,

  BUTTON_NBR,
};

class Menu {
public:
  Menu();
  ~Menu();
	int MenuManager(sf::RenderWindow &win, SpriteCreator &creator, std::array<float, 350> &arr, int &size);
  void setLobbyMenu(bool state);
  void setLauncherMenu(bool state);
  int drawLauncher(sf::RenderWindow &win);
  int drawLobby(sf::RenderWindow &win);
  int KeyLauncher();
  int KeyLobby();
  int HandleLauncherSelection();
  int HandleLobbySelection();
  void setReleased();
  // initLobbyMenu();
  void setButton(LauncherButton nb, std::string text, float xpos);
  void createButton(int i, SpriteCreator &creator);
  void createplayer(int i, SpriteCreator &creator);
  void createTitle(SpriteCreator &creator);
  void initLauncher(SpriteCreator &creator);
  void initLobby(SpriteCreator &creator);
  bool getReady();
  bool isPrintable(int i);
private:
  bool LauncherMenu = true;
  bool LobbyMenu = false;
  bool Launcherinit = false;
  bool Lobbyinit = false;
  std::vector<sf::Text > _Button;
  std::vector<sf::Sprite > _Sprite;
  sf::Font Font;
  unsigned int selection = 0;
  bool press = false;
  bool playerready = false;
  bool firsttime = false;
  std::vector<bool> _Player;
  std::vector<bool> _Ready;
  std::array<float, 350> _Floatcom;
};

#endif /* MENU_HANDLE */
