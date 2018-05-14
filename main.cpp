#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Object.h"
#include "Generation.h"
#include <iostream>
#include <sstream>

void human()
{
	Game game;
	game.startGame();
}

void hmmm()
{
	

	
	std::cout << "hmm() not working" << std::endl;
}

void hmm2()
{
	int gen_number = 0;
	//int mutationNumber = 0;
	//float lastScore = 0;
	Generation gen(0.005,0.0);
	while (true)
	{
		gen.play(); 
		std::cout << "Generation " << gen_number << " score: " << gen.score() << std::endl;
		gen.nextGen();
		gen_number++;
	}
	//gen.play();
	//while (true)
	//{
	//	float progress = gen.score(gen.maks()) - lastScore;
	//	std::cout << "Generation number: " << gen_number++ << ", max score:" << gen.score(gen.maks()) << ", progres: " << progress  << std::endl;
	//	lastScore = gen.score(gen.maks());
	//	//if (i % 10 == 0)
	//	{
	//		//if(gen.score(gen.maks())>6000)
	//			gen.visual(gen.maks());
	//		if (progress < 10)
	//		{
	//			gen.doubleMutationRate();
	//			mutationNumber++;
	//		}
	//		if (progress > 25 )
	//		{
	//			for (int i = 0; i < mutationNumber; i++)
	//				gen.halveMutationRate();
	//			mutationNumber = 0;
	//		}
	//		std::cout << "Mutation rate: " << mutationNumber << std::endl;
	//		//gen.visual(1);
	//		//std::cout << "Another? (Y/N) ";
	//		//std::cin >> a;
	//		//if (a == 'N')
	//			//break;
	//	}
	//	
	//	if (gen_number % 10 == 9)
	//	{
	//		std::ostringstream ss;
	//		ss << gen_number;
	//		gen.save("Generacja_" + ss.str() + ".txt");
	//	}
	//	gen.nextGen();
	//	gen.play();
	//}
	//std::cout << "End...";

	//gen.visual();
}

void load()
{
	//Generation gen(50);
	//std::cout << "Podaj nazwe pliku:" << std::endl;
	//std::string fileName;
	//std::cin >> fileName;
	//gen.load(fileName);
	//gen.visual(gen.maks());
	///*
	//int gen_number = 3;
	//gen.play();
	//while (true)
	//{
	//	std::cout << "Generation number: " << gen_number++ << ", max score:" << gen.score(gen.maks()) << std::endl;
	//	{
	//		//gen.visual(gen.maks());
	//	}
	//	std::ostringstream ss;
	//	ss << gen_number;
	//	//gen.save("Generacja_" + ss.str() + ".txt");
	//	gen.nextGen();
	//	gen.play();
	//}
	//*/
}

int main()
{
	srand(time(NULL));
	int a;
	std::cout << "JAki tryp? (1 - human; 2 - single object test; 3 - start teaching; 4 - load from file)" << std::endl;
	std::cin >> a;
	switch (a)
	{
	case 1:
		human();
		break;
	case 2:
		hmmm();
		break;
	case 3:
		hmm2();
		break;
	case 4:
		load();
		break;
	}
	std::cout << "Koniec." << std::endl;
	std::cin.get(); std::cin.get();
	return 0;
}