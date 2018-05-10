#include "Visual.h"

void Visual::moveCirce(int x, int y)
{
	circ.setPosition(x, y);
}

void Visual::moveEks(int x, int y)
{
	eks[0] = sf::Vertex(sf::Vector2f(x + SQUARESIZE / 8, y + SQUARESIZE / 8));
	eks[1] = sf::Vertex(sf::Vector2f(x + SQUARESIZE * 7 / 8, y + SQUARESIZE * 7 / 8));
	eks[2] = sf::Vertex(sf::Vector2f(x + SQUARESIZE / 8, y + SQUARESIZE * 7 / 8));
	eks[3] = sf::Vertex(sf::Vector2f(x + SQUARESIZE * 7 / 8, y + SQUARESIZE / 8));
}

Visual::Visual()
{
	std::cout << "Start visual game.." << std::endl;
	window.create(sf::VideoMode(WINDOWX, WINDOWY), "Gomoku");

	lines = new sf::Vertex[(BOARDSIZE + 1)*(BOARDSIZE + 1)];
	for (int i = 0; i < 32; i += 2)
	{
		//vertical
		lines[i] = sf::Vertex(sf::Vector2f(SQUARESIZE / 2, SQUARESIZE / 2 + i / 2 * SQUARESIZE));
		lines[i + 1] = sf::Vertex(sf::Vector2f(SQUARESIZE / 2 + BOARDSIZE * SQUARESIZE, SQUARESIZE / 2 + i / 2 * SQUARESIZE));
		//horisontal
		lines[i + (BOARDSIZE + 1) * 2] = sf::Vertex(sf::Vector2f(SQUARESIZE / 2 + i / 2 * SQUARESIZE, SQUARESIZE / 2));
		lines[i + (BOARDSIZE + 1) * 2 + 1] = sf::Vertex(sf::Vector2f(SQUARESIZE / 2 + i / 2 * SQUARESIZE, SQUARESIZE / 2 + BOARDSIZE * SQUARESIZE));
	}

	eks = new sf::Vertex[4];
	float r = SQUARESIZE * 5 / 16;
	circ = sf::CircleShape(r);
	circ.setFillColor(sf::Color::Black);
	circ.setOutlineColor(sf::Color::White);
	circ.setOutlineThickness(1);
	circ.setOrigin(sf::Vector2f(r, r));

}

void Visual::update()
{
	sf::Event event;
	//sf::Mouse m;
	//sf::Vector2i mouse = m.getPosition(window);
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		/*if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{

			int tmpx = (mouse.x - SQUARESIZE / 2) / SQUARESIZE;
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

		}*/
	}
}

void Visual::draw(int **board)
{
	window.clear(sf::Color::Black);
	window.draw(lines, (BOARDSIZE + 1)*(BOARDSIZE + 1), sf::Lines);
	for (int i = 0; i<BOARDSIZE; i++)
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (board[i][j] == 1)
			{
				moveCirce(i*SQUARESIZE + SQUARESIZE, j*SQUARESIZE + SQUARESIZE);
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

void Visual::sleep()
{
	sf::sleep(sf::seconds(DELTATIME));
}

Visual::~Visual()
{
	delete[] lines;
	delete[] eks;
}
