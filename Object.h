#pragma once

#include "Game.h"
#include "NeuralNet.h"
#include <iostream>


class Game;

class Object
{
protected:
	NeuralNet * brain;
	Game* gra;

	int generateTrainingExamples(int**&x, float**&y);
public:
	//almost never use it
	Object();
	
	//input neurons, hidden neruons, output nerons
	Object(int, int*);
	Object(const Object&);


	//makes AI play the game. Parametr tells if it should be visible, or only make score
	double graj(bool = 0, NeuralNet* op=nullptr);
	NeuralNet* getBrain();

	void learn(float lambda,float mi);

	//friend std::ostream& operator<<(std::ostream& out, const Object& z);
	//friend std::istream& operator>>(std::istream& in, Object& z);

	~Object();
};