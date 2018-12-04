/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** Menu handler
*/

#include <iostream>
#include <SFML/Graphics.hpp>

#include "MenuHandle.hpp"

Menu::Menu() {
    if (!Font.loadFromFile("SFML/assets/font/8-BIT WONDER.TTF"))
      std::cerr << "Error loading Font" << std::endl;
    for (size_t i = 0, count = 4; i < count; i++) {
      _Player.push_back(false);
      _Ready.push_back(false);
    }
}

Menu::~Menu() {

}

void Menu::initLauncher(SpriteCreator &creator) {
  for (size_t i = 0; i < BUTTON_NB; i++) {
    sf::Text empty;
    _Button.push_back(empty);
  }
  setButton(SOLO, "Solo", PADDING);
  setButton(MULTI, "Local Game", PADDING + LPADDING);
  setButton(QUIT, "Quit", PADDING + LPADDING + LPADDING);
  Launcherinit = true;
  createButton(0, creator);
  createButton(1, creator);
  createButton(2, creator);
  createTitle(creator);
}

void Menu::initLobby(SpriteCreator &creator) {
  selection = 0;
  for (size_t i = 0; i < BUTTON_NB; i++) {
    sf::Text empty;
    _Button.push_back(empty);
  }
  setButton(SOLO, "Back", PADDING);
  setButton(MULTI, "Not Ready", PADDING + LPADDING);
  setButton(QUIT, "Ready", PADDING + LPADDING);
  Lobbyinit = true;
  createButton(0, creator);
  createButton(1, creator);
  for (size_t i = 0, count = 4; i < count; i++)
    createplayer(i, creator);
  createTitle(creator);
}

int Menu::MenuManager(sf::RenderWindow &win, SpriteCreator &creator,
		      std::array<float, 250> &arr, int &size) {

	for (int i = 0; i < size; i++) {
		_Player[i] = true;
		if (arr[i] == 1)
			_Ready[i] = true;
    if (int(arr[i]) % 10 == 0)
			_Ready[i] = false;
	}
  if (LauncherMenu) {
    if (!Launcherinit)
      initLauncher(creator);
    return (drawLauncher(win));
  }
  else if (LobbyMenu) {
    if (!Lobbyinit)
      initLobby(creator);
    return (drawLobby(win));
  }
  return 0;
}

void Menu::setLobbyMenu(bool state) {
  LobbyMenu = state;
}

void Menu::setLauncherMenu(bool state) {
  LauncherMenu = state;
}

void Menu::setButton(LauncherButton nb, std::string text, float xpos) {
  _Button[nb].setFont(Font);
  _Button[nb].setCharacterSize(20);
  _Button[nb].setString(text);
  _Button[nb].setPosition({ MARGIN, xpos});
}

void Menu::setReleased() {
  press = false;
}

int Menu::HandleLauncherSelection() {
  switch (selection) {
    case 0:
      return 1;
    case 1:
      setLauncherMenu(false);
      setLobbyMenu(true);
      Launcherinit = false;
      _Sprite.clear();
      _Button.clear();
      return 2;
    case 2:
      return 84;
  }
  return 0;
}

int Menu::HandleLobbySelection()
{
  switch (selection) {
    case 0:
      setLauncherMenu(true);
      setLobbyMenu(false);
      Lobbyinit = false;
      _Sprite.clear();
      _Button.clear();
      playerready = false;
      return 2;
    case 1:
      if (playerready) {
        playerready = false;
        firsttime = true;
      }
      else {
        playerready = true;
        firsttime = true;
      }
      return 3;
  }
  return 0;
}

int Menu::KeyLauncher()
{
  if (!press) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
      press = true;
      if (HandleLauncherSelection() != 0)
        return HandleLauncherSelection();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      if (selection == 0)
        selection = 2;
      else
        selection -=1;
      press = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      selection +=1;
      press = true;
    }
  }
  selection = selection % 3;
  return 0;
}

int Menu::KeyLobby() {
  if (!press) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
      press = true;
      if (HandleLobbySelection() != 0)
        return (HandleLobbySelection());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      if (selection == 0)
        selection = 1;
      else
        selection -=1;
      press = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      selection +=1;
      press = true;
    }
  }
  selection = selection % 2;
  return 0;
}

void Menu::createTitle(SpriteCreator &creator) {
  _Sprite.push_back(creator.createSprite(TITLE));
  _Sprite.back().setPosition(MIDSCREEN + LPADDING * 2, MIDSCREEN - PADDING);
}

// create an empty Button
void Menu::createButton(int i, SpriteCreator &creator) {
  _Sprite.push_back(creator.createSprite(BUTTON));
  _Sprite.back().setPosition(0, PADDING + (LPADDING * i) - CENTER);
}

// Create a spaceship player
void Menu::createplayer(int i, SpriteCreator &creator) {
  spriteType I = static_cast<spriteType>(SHIP1 + i);
  _Sprite.push_back(creator.createSprite(I));
  _Sprite.back().setScale(3, 3);
  _Sprite.back().setPosition((MIDSCREEN * ((i % 2) + 1)) + PADDING, MIDSCREEN * ((i / 2) + 1));
  spriteType Y = static_cast<spriteType>(READY);
  _Sprite.push_back(creator.createSprite(Y));
  _Sprite.back().setPosition((MIDSCREEN * ((i % 2) + 1)) + PADDING, MIDSCREEN * ((i / 2) + 1));
}

int Menu::drawLauncher(sf::RenderWindow &win) {
  if (KeyLauncher() != 0)  {
    return HandleLauncherSelection();
  }

  for (size_t i = 0; i < BUTTON_NB; i++) {
    if (i == selection)
      _Button[selection].setFillColor(sf::Color::Blue);
    else
      _Button[i].setFillColor(sf::Color::White);
    win.draw(_Sprite[i]);
    win.draw(_Button[i]);
  }
  win.draw(_Sprite.back());
  return 0;
}

bool Menu::isPrintable(int i) {
  // if (_Player[i])
  //   printf("%i\n", i);
  if (i > 1) {
    if (i % 2 == 0)
      if (!_Player[(i - 2)/2])
        return false;
    if (i % 2 == 1)
      if (!_Ready[(i - 3)/2])
        return false;
  }
  return true;
}

int Menu::drawLobby(sf::RenderWindow &win) {
  if (KeyLobby() != 0)
    return (HandleLobbySelection());
  for (size_t i = 0; i < _Sprite.size(); i++) {
    if (isPrintable(i))
      win.draw(_Sprite[i]);
    if (i == selection)
      _Button[i].setFillColor(sf::Color::Blue);
    else if (i < 3)
      _Button[i].setFillColor(sf::Color::White);
    if (i == 2 && selection == 1)
      _Button[i].setFillColor(sf::Color::Blue);
    if (i < 3 && (i == 0 || (playerready && i == 2)))
      win.draw(_Button[i]);
    if (!playerready)
      win.draw(_Button[1]);
  }
  win.draw(_Sprite.back());
  return 0;
}

bool Menu::getReady()
{
  if (firsttime) {
    firsttime = false;
    return true;
  }
  return false;
}
