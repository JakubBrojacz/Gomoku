#include "Game.h"


Game::Game(NeuralNet* owner) : owner(owner), opponent(nullptr)
{
}

double Game::startGame(status st, bool visibility, NeuralNet* op)
{
	if (st == HUMAN)
	{
		//engine = new Engine();
		//while (engine->update());
		//int tmp = engine->endGame();
		//delete engine;
		//engine = nullptr;
		//return tmp;
		std::cout << "ERROR: Nie zaimplementowany Human Mode" << std::endl;
		return 0.0;
	}
	else
	{
		if (!op)
		{
			std::cout << "ERROR: Play without opponent" << std::endl;
			return 0;
		}
		opponent = op;
		/*
#ifdef SAMESEED
		srand(2); //always sratr the same game 
#endif // SAMESEED
#ifndef SAMESEED
		if (visibility)
		{
			srand(owner->getSeed());
		}
		else
		{
			owner->generateSeed();
			srand(owner->getSeed());
		}
		
#endif // !SAMESEED
*/
		

		aiengine = new AIEngine(visibility);
		//sf::sleep(sf::seconds(2)); <- usefull for manual playing

		//CREATING VECTORS OF INFORMATION
		float* s;
		s = new float[INPUTNODES]; //sensor vector
		bool* d;
		d = new bool[OUTPUTNODES]; //output vector - keyboard keys
		float* d_begin; //output in raw form
		d_begin = new float[OUTPUTNODES];
		for (int i = 1; i < INPUTNODES; i++)
			s[i] = 0; //first sensor informations
		s[0] = 1;

		//CREATE ACTUAL PLAYER
		bool actual = 0;
		NeuralNet* act = owner;

		//MAIN LOOP
		do
		{
			//GET NEXT MOVE FROM BRAIN
			delete d_begin;
			d_begin = act->output(s, INPUTNODES);
			for (int i = 0; i < OUTPUTNODES; i++)
				if (d_begin[i] > 0.7) //convert float to bool
					d[i] = 1;
				else
					d[i] = 0;

			//MAKE THAT MOVE
			delete s;
			s=aiengine->update(d);  //gain new sensor vector

			//CHANGE ACTUAL PLAYER
			if (actual)
				act = owner;
			else
				act = opponent;
			actual = !actual;
		} while (s[0]<100); //s[0]>=100 == game is lost

		//FINISH GAME - GET SCORE
		aiengine->endGame(); 
		double tmp = actual ? 1 : 0;
		delete aiengine;
		aiengine = nullptr;
		return tmp;
	}
	
}

Game::~Game()
{
	//if (engine) delete engine; 
	if (aiengine) delete aiengine; 
}
