#pragma once
#include <iostream>
#include <math.h>
#include "config.h"

class Matrix {

	//local variables
	int rows;
	int cols;
	float** matrix;

	//activation function
	float sigmoid(float x);
	float sigmoidDerivative(float x);
public:
	Matrix(int r, int c); //rows, colums

	//i dont use it..
	//but it works :D
	Matrix(Matrix& d);


	//multioplication (dot product)
	Matrix* dot(Matrix* n);

	Matrix* transpose();

	Matrix* hadamard(Matrix* n);

	//between -1,1
	void randomize();


	//Creates a single column array from the parameter array
	static Matrix* singleColumnMatrixFromArray(float* arr, int l);
	static Matrix* singleColumnMatrixFromArray(int* arr, int l);

	//sets this matrix from an array
	void fromArray(float* arr, int l);
	

	//returns an array which represents this matrix
	float* toArray();

	//add one row of bias
	Matrix* addBias();
	Matrix* deleteBias();

	//call activation function on matrix or its derivative
	Matrix* activate();
	Matrix* activeDerivative();

	Matrix* removeBottomLayer();

	void GradientDescentSubtract(Matrix * a, Matrix * delta, float lambda);

	void FinalGradientDescentWeightMatrix(Matrix * a, float mi, float lambda, int n);

	//copying constructor another way ... With pointers :D
	Matrix* clone();

	~Matrix();

	float& operator()(int i, int j);
	friend std::ostream& operator<<(std::ostream& out, const Matrix& d);
	friend std::istream& operator>>(std::istream& in, Matrix& d);
};

