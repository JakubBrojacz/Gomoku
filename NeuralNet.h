#pragma once
#include "Matrix.h"
#include <iostream>
#include <time.h>

class NeuralNet {



	Matrix** weights;
	int n_layer;
	int* layer;

	unsigned int seed;

	//for gradient descent
	//see in cpp file
	void zl_al(Matrix ** &al, Matrix ** &zl, int * board, int n);
	Matrix ** GradientDescent_1(Matrix ** &zl, Matrix * a, float * y, int n2);
	Matrix * DeltaL(float * a, float * y);
public:
	NeuralNet(int n_layer, int* l);

	NeuralNet(NeuralNet& d);


	void GradientDescent(int m, int*board[], int n1, float* y[], int n2, float lambda, float mi); //nwm parametry + output

	


	//the way brain thinks
	float* output(float* inputsArr, int l);


	//copy constructor with pointer
	NeuralNet* clone();

	~NeuralNet();

	friend std::ostream& operator<<(std::ostream& out, const NeuralNet& d);
	friend std::istream& operator>>(std::istream& in, NeuralNet& d);
};