//
// EPITECH PROJECT, 2018
// cpp
// File description:
// cpp
//

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "MenuHandle.hpp"
#include "Background.hpp"
#include "SpriteCreator.hpp"
#include "Component.hpp"
#include "Controls.hpp"

class Graphics {
public:
	Graphics();
	~Graphics();
	int startDisplay(std::array<float, 350> &arr, int &size);
	bool display(std::vector<std::vector<float>> compSent, Controls &controls, Sound &sound, bool gameover);
	int Launcher(SpriteCreator &creator, std::array<float, 350> &arr, int &size);
	void getComponents(std::vector<std::vector<float>> compSent);
	bool checkIfCompExist(spriteType type, int num, sf::Vector2f newPos);
	void removeSomeComp(std::vector<std::vector<float>> compSent);
	void close();
	void printgameover();
private:
       sf::RenderWindow window;
			 sf::Event event;
			 Menu menu;
			 SpriteCreator creator;
			 Background background;
			 std::vector<Component> components;
			 bool gameoverinit = false;
			 sf::Sprite gameover;
};

#endif /* GRAPHICS_HPP */
