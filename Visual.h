#pragma once

#include "config.h"
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <iostream>

class Visual
{
protected:
	sf::RenderWindow window;
	sf::CircleShape circ;
	sf::Vertex* eks;
	sf::Vertex* lines;

	void moveCirce(int, int);
	void moveEks(int, int);
public:
	Visual();

	void update();
	void draw(int**);
	void sleep();

	~Visual();
};