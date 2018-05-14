#include "Generation.h"





Generation::Generation(float lambda, float mi) : learningRate(lambda), regulationRate(mi) 
{
	std::cout << "Initiating..." << std::endl;
	int a[2] = { 2,2 };
	gen = new Object(2, a); //...
}

void Generation::play()
{
	//std::cout << "Playing..." << std::endl;


	wyn = gen->graj(1, gen->getBrain()); 
		
}

void Generation::nextGen()
{
	//std::cout << "Creating new generation..." << std::endl;
	
	gen->learn(learningRate, regulationRate);
}

/*
void Generation::doubleMutationRate()
{
	mutationRate *= 2.f;
}

void Generation::halveMutationRate()
{
	mutationRate /= 2.f;
}
*/


double Generation::score()
{
	return wyn;
}

void Generation::visual()
{
	play();
}

/*
void Generation::save(std::string file)
{
	std::cout << "Saving..." << std::endl;
	std::fstream f;
	f.open(file, std::ios::out, std::ios::trunc);
	if (!f.good())
	{
		std::cout << "Generation saved - Failed" << std::endl;
		return;
	}
	for (int i = 0; i < num; i++)
		f << wyn[i] << std::endl;
	for (int i = 0; i < num; i++)
		f << (*gen[i]) << std::endl;
	f.close();
	std::cout << "Generation saved - Success" << std::endl;
}

void Generation::load(std::string file)
{
	std::fstream f;
	f.open(file, std::ios::in);
	if (!f.good())
	{
		std::cout << "ERROR: Bad file namy" << std::endl;
		return;
	}
	for (int i = 0; i < num; i++)
	{
		f >> wyn[i];
	}
	for (int i = 0; i < num; i++)
		f >> (*gen[i]);
	f.close();
}
*/