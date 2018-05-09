#include "AIEngine.h"




void AIEngine::moveCirce(int x, int y)
{
	circ.setPosition(x, y);
}

void AIEngine::moveEks(int x,int y)
{
	eks[0] = sf::Vertex(sf::Vector2f(x+SQUARESIZE / 8, y+SQUARESIZE / 8));
	eks[1] = sf::Vertex(sf::Vector2f(x+SQUARESIZE * 7 / 8, y+SQUARESIZE * 7 / 8));
	eks[2] = sf::Vertex(sf::Vector2f(x+SQUARESIZE / 8, y+SQUARESIZE * 7 / 8));
	eks[3] = sf::Vertex(sf::Vector2f(x+SQUARESIZE * 7 / 8, y+SQUARESIZE / 8));
}

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
		window.create(sf::VideoMode(WINDOWX, WINDOWY), "Gomoku");

	lines = new sf::Vertex[(BOARDSIZE+1)*(BOARDSIZE+1)];
	for (int i = 0; i < 32; i+=2)
	{
		//vertical
		lines[i] = sf::Vertex( sf::Vector2f(SQUARESIZE / 2, SQUARESIZE / 2 + i/2 * SQUARESIZE) );
		lines[i+1] = sf::Vertex(sf::Vector2f(SQUARESIZE / 2 + BOARDSIZE * SQUARESIZE, SQUARESIZE / 2 + i/2 * SQUARESIZE));
		//horisontal
		lines[i + (BOARDSIZE+1)*2] = sf::Vertex(sf::Vector2f(SQUARESIZE / 2 + i/2 * SQUARESIZE, SQUARESIZE / 2));
		lines[i + (BOARDSIZE+1)*2+1] = sf::Vertex(sf::Vector2f(SQUARESIZE / 2 + i/2 * SQUARESIZE, SQUARESIZE / 2 + BOARDSIZE * SQUARESIZE));
	}

	eks = new sf::Vertex[4];
	float r = SQUARESIZE * 5 / 16;
	circ = sf::CircleShape(r);
	circ.setFillColor(sf::Color::Black);
	circ.setOutlineColor(sf::Color::White);
	circ.setOutlineThickness(1);
	circ.setOrigin(sf::Vector2f(r, r));
	/*
	eks[0] = sf::Vertex(sf::Vector2f(SQUARESIZE / 8, SQUARESIZE / 8));
	eks[1] = sf::Vertex(sf::Vector2f(SQUARESIZE * 7 / 8, SQUARESIZE * 7 / 8));
	eks[2] = sf::Vertex(sf::Vector2f(SQUARESIZE / 8, SQUARESIZE * 7 / 8));
	eks[3] = sf::Vertex(sf::Vector2f(SQUARESIZE * 7 / 8, SQUARESIZE / 8));
	*/

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
		sf::sleep(sf::seconds(DELTATIME));
	}
	else
	{
		//lifespan?
	}

	//STEERING
	if (visibility)
	{
		sf::Event event;
		sf::Mouse m;
		sf::Vector2i mouse = m.getPosition(window);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				
				int tmpx = (mouse.x-SQUARESIZE/2)/SQUARESIZE;
				int tmpy = (mouse.y - SQUARESIZE / 2) / SQUARESIZE;
				if (tmpx < BOARDSIZE && tmpy < BOARDSIZE && !board[tmpx][tmpy])
				{
					if (actualPlayer)
						board[tmpx][tmpy] = 1;
					else
						board[tmpx][tmpy] = -1;
					//std::cout << tmpx << " " << tmpy << std::endl;
					if (win(tmpx, tmpy))
					{
						float* sences = new float[1];
						sences[0] = 200;
						return sences;
					}
					actualPlayer = !actualPlayer;
				}
				
			}
		};
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
		window.clear(sf::Color::Black);
		window.draw(lines, (BOARDSIZE+1)*(BOARDSIZE+1), sf::Lines);
		for(int i=0;i<BOARDSIZE;i++)
			for (int j = 0; j < BOARDSIZE; j++)
			{
				if (board[i][j] == 1)
				{
					moveCirce(i*SQUARESIZE+SQUARESIZE, j*SQUARESIZE+SQUARESIZE);
					window.draw(circ);
				}
				else if (board[i][j] == -1)
				{
					moveEks(i*SQUARESIZE + SQUARESIZE / 2, j*SQUARESIZE + SQUARESIZE / 2);
					window.draw(eks, 4, sf::Lines);
				}
			}
		window.display();
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
		window.close();
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
	delete[] lines;
	delete[] eks;
	for (int i = 0; i < BOARDSIZE; i++)
		delete[] board[i];
	delete[] board;
}
