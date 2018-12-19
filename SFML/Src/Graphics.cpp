/*
** EPITECH PROJECT, 2018
** CPP_rtype_2018
** File description:
** rtype
*/

#include "Graphics.hpp"
#include <iostream>

Graphics::Graphics() : window(sf::VideoMode(1920, 1080), "R-Type"), background(creator)
{

}

Graphics::~Graphics()
{

}

void Graphics::close()
{
	std::cout << "Closing window" << std::endl;
	window.close();
}

int Graphics::Launcher(SpriteCreator &creator, std::array<float, 350> &arr, int &size) {
	int r = 0;

	r = menu.MenuManager(window, creator, arr, size);
	if (r == 84) {
		window.close();
		exit(0);
	}
	return r;
}

int Graphics::startDisplay(std::array<float, 350> &arr, int &size)
{
	// menu.setLauncherMenu(true);
	if (!window.isOpen())
		return 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
              window.close();
		if (event.type == sf::Event::EventType::KeyReleased)
							menu.setReleased();
	}
	window.clear();
	background.display(window);
	switch (Launcher(creator, arr, size)) {
		case 0:
			break;
		case 1:
			return 3;
		case 2:
			break;
	}
	window.display();
	if (menu.getReady())
		return 2;
	return 1;
}

bool Graphics::checkIfCompExist(spriteType type, int num, sf::Vector2f newPos)
{
	for (auto& comp : components) {
		if (comp.getType() == type && comp.getNum() == num) {
			comp.setPos(newPos);
			return true;
		}
	}
	return false;
}

void Graphics::removeSomeComp(std::vector<std::vector<float>> compSent)
{
	bool exist = false;

	for (size_t i = 0; i < components.size(); i++) {
		for (auto& comp : compSent) {
			if (components[i].getType() == comp[0] && components[i].getNum() == comp[1])
				exist = true;
		}
		if (!exist) {
			// if (components[i].getAnimState())
			// 	components[i].playAnimation();
			// else if (!components[i].getPlayAnim()) {
				components.erase(components.begin() + i);
				i--;
			// }
		}
		exist = false;
	}
}

void Graphics::printgameover()
{
	if (!gameoverinit) {
		gameoverinit = true;
		gameover = creator.createSprite(GAMEOVER);
	}
	gameover.setPosition(700.f, 400.f);
	window.draw(gameover);
}

void Graphics::getComponents(std::vector<std::vector<float>> compSent)
{
	std::vector<std::string> params;

	removeSomeComp(compSent);
	for (auto& comp : compSent) {
		if (!checkIfCompExist(static_cast<spriteType>(comp[0]), comp[1], sf::Vector2f(comp[2], comp[3]))) {
			components.push_back(Component(static_cast<spriteType>(comp[0]),
			comp[1],
			sf::Vector2f(comp[2], comp[3]),
			creator));
		}
	}
}

bool Graphics::display(std::vector<std::vector<float>> compSent, Controls &controls, Sound &sound, bool gameover)
{
	if (window.isOpen()) {
		window.clear();
		background.display(window);
		getComponents(compSent);
		controls.checkControls(sound);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			return false;
		}
		if (gameover)
			printgameover();
		for (auto& comp : components)
			window.draw(comp.getSprite());
		window.display();
		return true;
	}
	return false;
}
