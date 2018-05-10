#pragma once

#include <iostream>
#include "config.h"
#include "Visual.h"


class AIEngine
{
protected:
	double points;


	bool visibility;
	Visual* window;

	bool actualPlayer; // 0 - circle, 1 - eks
	bool madeMove;
	int** board;

	bool win(int, int);
public:

	AIEngine(bool visibility = 1); //visibility, refreshing rate

	float* update(bool*);
	double endGame();

	~AIEngine();
};