#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include "config.h"
#include "Player.h"


class AIEngine
{
protected:
	double points;


	sf::RenderWindow window;
	bool visibility;

	sf::CircleShape circ;
	sf::Vertex* eks;
	sf::Vertex* lines;

	bool actualPlayer; // 0 - circle, 1 - eks
	bool madeMove;
	int** board;

	void moveCirce(int,int);
	void moveEks(int,int);
	bool win(int, int);
public:

	AIEngine(bool visibility = 1); //visibility, refreshing rate

	float* update(bool*);
	double endGame();

	~AIEngine();
};