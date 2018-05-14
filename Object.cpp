#include "Object.h"
#include <iostream>

int Object::generateTrainingExamples(int ** &x, float ** &y)
{
	y = new float*[100];
	x = new int*[100];
	for (int i = 0; i < 100; i++)
	{
		y[i] = new float[2];
		x[i] = new int[2];
		x[i][0] = rand() % 2;
		x[i][1] = rand() % 2;
		y[i][0] = !(x[i][0] && x[i][1]);
		y[i][1] = (x[i][0] && x[i][1]);
	}
	return 100;
}

Object::Object()
{
	std::cout << "ERROR: empty constructor of class Object" << std::endl; //I said to not use this
}


Object::Object(int n,int* layer)
{
	brain = new NeuralNet(n,layer);
	gra = new Game(brain);
}

Object::Object(const Object &d)
{
	brain = d.brain->clone();
	gra = new Game(brain);
}


double Object::graj(bool visibility, NeuralNet* op)
{
	//return gra->startGame(AI,visibility, op);
	float score = 0; 
	for (int i = 0; i < 25; i++)
	{
		int x[2] = { rand() % 2,rand() % 2 };
		float x2[2] = { x[0],x[1] };
		float* y = brain->output(x2, 2);
		if (y[0] > y[1])
			score += !(x[0] && x[1]);
		else
			score += (x[0] && x[1]);
	}
	score /= 25.0;
	return score;
	
}

NeuralNet * Object::getBrain()
{
	return brain;
}

void Object::learn(float lambda, float mi)
{
	
	float** y=nullptr;
	int** x=nullptr;
	int n = generateTrainingExamples(x, y);
	brain->GradientDescent(n, x, 2, y, 2, lambda, mi);
}




Object::~Object()
{
	delete brain;
	delete gra;
}


//std::ostream & operator<<(std::ostream & out, const Object & z)
//{
//	out << *(z.brain);
//	return out;
//}
//
//std::istream & operator>>(std::istream & in, Object & z)
//{
//	in >> *(z.brain);
//	return in;
//}
