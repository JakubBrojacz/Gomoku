#pragma once

#include "Object.h"
#include <vector>
#include <fstream>

class Generation
{
private:
	Object* gen; //all objects in current generation - 1
	double wyn; //their (his) score

	float learningRate; 
	float regulationRate;
public:
	//choose number of generated objects
	Generation(float lambda, float mi);

	//make everyone play and test their skills (update wyn)
	void play();

	//mutate everyone based on wyn (better play() first)
	void nextGen();

	//void doubleMutationRate();
	//void halveMutationRate();

	//get score of given index
	double score();

	//make object play, so we can see it (parametr - index of object)
	void visual();

	//void save(std::string file);
	//void load(std::string file);
};