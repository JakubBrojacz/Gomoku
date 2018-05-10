#include "AIEngine.h"



bool AIEngine::win(int x, int y)
{
	int player = board[x][y];
	if (x > 3)
	{
		bool win = 1;
		for(int i=-4;i<0;i++)
			if (board[x+i][y] != player)
			{
				win = 0;
				break;
			}
		if (win)
			return true;
		if (y > 3)
		{
			bool win = 1;
			for (int i = - 4; i<0; i++)
				if (board[x+i][y+i] != player)
				{
					win = 0;
					break;
				}
			if (win)
				return true;
		}
		if (y < BOARDSIZE-4)
		{
			bool win = 1;
			for (int i = -4; i<0; i++)
				if (board[x + i][y - i] != player)
				{
					win = 0;
					break;
				}
			if (win)
				return true;
		}
	}
	if (x < BOARDSIZE-4)
	{
		bool win = 1;
		for (int i = -4; i<0; i++)
			if (board[x-i][y] != player)
			{
				win = 0;
				break;
			}
		if (win)
			return true;
		if (y > 3)
		{
			bool win = 1;
			for (int i = -4; i<0; i++)
				if (board[x-i][y + i] != player)
				{
					win = 0;
					break;
				}
			if (win)
				return true;
		}
		if (y < BOARDSIZE-4)
		{
			bool win = 1;
			for (int i = -4; i<0; i++)
				if (board[x - i][y - i] != player)
				{
					win = 0;
					break;
				}
			if (win)
				return true;
		}
	}
	if (y < BOARDSIZE-4)
	{
		bool win = 1;
		for (int i = -4; i < 0; i++)
			if (board[x][y-i] != player)
			{
				win = 0;
				break;
			}
		if (win)
			return true;
	}
	if (y > 3)
	{
		bool win = 1;
		for (int i = -4; i < 0; i++)
			if (board[x][y + i] != player)
			{
				win = 0;
				break;
			}
		if (win)
			return true;
	}
	return false;
}

AIEngine::AIEngine(bool visibility) :visibility(visibility)
{
	if (visibility)
		window = new Visual();

	board = new int*[BOARDSIZE];
	for (int i = 0; i < BOARDSIZE; i++)
		board[i] = new int[BOARDSIZE];
	for (int i = 0; i < BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
			board[i][j] = 0;

	madeMove = 1;
}



float * AIEngine::update(bool *keyboard)
{
	//IF OPPONENT SURRENDERED
	if (!madeMove)
	{
		float* sences = new float[1];
		sences[0] = 200;
		return sences;
	}


	// UPDATE TIME
	if (visibility)
	{
		window->sleep();
	}
	else
	{
		//lifespan?
	}

	//STEERING
	if (visibility)
	{
		window->update(); //in case you move your mouse xD
	}

	//AI MOVE
	madeMove = 0;
	for(int i=0;i<BOARDSIZE*BOARDSIZE;i++)
		if(!board[i/ BOARDSIZE][i%BOARDSIZE] && keyboard[i])
		{
			if (actualPlayer)
				board[i/ BOARDSIZE][i%BOARDSIZE] = 1;
			else
				board[i/ BOARDSIZE][i%BOARDSIZE] = -1;
			//std::cout << tmpx << " " << tmpy << std::endl;
			if (win(i/ BOARDSIZE, i%BOARDSIZE))
			{
				float* sences = new float[1];
				sences[0] = 200;
				return sences;
			}
			actualPlayer = !actualPlayer;
			madeMove = 1;
			break;
		}
	

	//VISUALIZATION
	if (visibility)
	{
		window->draw(board);
	}


	
	//CREATE OUTPUT
	float* sences = new float[INPUTNODES];
	for (int i = 0; i < INPUTNODES; i++)
	{
		sences[i] = board[i/BOARDSIZE][i%BOARDSIZE];
	}
	
	
	//if (visibility)
	//	for(int i=0;i<8;i++)
	//		std::cout << sences[i*3+1] <<  std::endl;
	//float* sences = new float[INPUTNODES];
	//for (int i = 0; i < INPUTNODES; i++)
	//	sences[i] = 0;
	return sences;
}

double AIEngine::endGame()
{
	//std::cout << "End game";
	//else
	//	points = 0;
	if (visibility)
	{
		delete window;
		window = nullptr;
	}
		
	if (visibility)
	{
		std::cout << "Live score: none" << std::endl;
		std::cout << "Points: none"  << std::endl;
		std::cout << "Life time: none"  << std::endl;
		std::cout << "Total points: none" << std::endl;
		if (actualPlayer)
			std::cout << "Win ens" << std::endl;
		else
			std::cout << "Win circle" << std::endl;
	}
	
	return 0;
}

AIEngine::~AIEngine()
{
	delete window;
	for (int i = 0; i < BOARDSIZE; i++)
		delete[] board[i];
	delete[] board;
}
