#include "Matrix.h"

float Matrix::sigmoid(float x)
{
	float y = 1 / (1 + exp(-x));
	return y;
	//if (x > 0)
	//	return 1;
	//return 0;
}

float Matrix::sigmoidDerivative(float x)
{
	return sigmoid(x)*(1-sigmoid(x));
}

Matrix::Matrix(int r, int c) : rows(r),cols(c)
{
	matrix = new float*[rows];
	for (int i = 0; i<rows; i++)
		matrix[i] = new float[cols];
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j<cols; j++) {
			matrix[i][j] = 0.f;
		}
	}
}

Matrix::Matrix(Matrix & d)
	: rows(d.rows), cols(d.cols)
{
	matrix = new float*[rows];
	for (int i = 0; i<rows; i++)
		matrix[i] = new float[cols];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j] = d.matrix[i][j];
}

Matrix * Matrix::dot(Matrix * n)
{
	Matrix* result = new Matrix(rows, n->cols);

	if (cols == n->rows) {
		//for each spot in the new matrix
		for (int i = 0; i<rows; i++) {
			for (int j = 0; j<n->cols; j++) {
				float sum = 0;
				for (int k = 0; k<cols; k++) {
					sum += matrix[i][k] * n->matrix[k][j];
				}
				result->matrix[i][j] = sum;
			}
		}
	}
	else
	{
		std::cout << "ERROR: Matrix cannot calculate dot produckt, matrix dimentions are bad" << std::endl;
		throw std::exception("ERROR: Matrix cannot calculate dot produckt, matrix dimentions are bad");
	}

	return result;
}

Matrix * Matrix::transpose()
{
	Matrix* tmp = new Matrix(cols, rows);
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++)
			tmp->matrix[i][j] = matrix[j][i];
	return tmp;
}

Matrix * Matrix::hadamard(Matrix * n)
{
	Matrix* tmp = new Matrix(*this);
	if (!(rows != n->rows || cols != n->cols))
	{
		std::cout << "Matrix dimensions doesnt match: Hadamard" << std::endl;
		throw std::exception("Matrix dimensions doesnt match: Hadamard");
		return tmp;
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			tmp->matrix[i][j] *= n->matrix[i][j];
	return tmp;
}

void Matrix::randomize()
{
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j<cols; j++) {
			matrix[i][j] = ((float)rand() / (float)RAND_MAX)*2.f - 1.f;
		}
	}
}

Matrix * Matrix::singleColumnMatrixFromArray(float * arr, int l)
{
	Matrix* n = new Matrix(l, 1);
	for (int i = 0; i< l; i++) {
		n->matrix[i][0] = arr[i];
	}
	return n;
}

Matrix * Matrix::singleColumnMatrixFromArray(int * arr, int l)
{
	Matrix* n = new Matrix(l, 1);
	for (int i = 0; i< l; i++) {
		n->matrix[i][0] = arr[i];
	}
	return n;
}

void Matrix::fromArray(float * arr, int l)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = arr[j + i * cols];
		}
	}
}

float * Matrix::toArray()
{
	float* arr = new float[rows*cols];
	for (int i = 0; i< rows; i++) {
		for (int j = 0; j< cols; j++) {
			arr[j + i * cols] = matrix[i][j];
		}
	}
	return arr;
}

Matrix * Matrix::addBias()
{
	Matrix* n = new Matrix(rows + 1, 1);
	for (int i = 0; i<rows; i++) {
		n->matrix[i][0] = matrix[i][0];
	}
	n->matrix[rows][0] = 1;
	return n;
}

Matrix * Matrix::deleteBias()
{
	Matrix* n = new Matrix(rows - 1, 1);
	for (int i = 0; i<rows-1; i++) {
		n->matrix[i][0] = matrix[i][0];
	}
	return n;
}

Matrix * Matrix::activate()
{
	Matrix* n = new Matrix(rows, cols);
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j<cols; j++) {
			n->matrix[i][j] = sigmoid(matrix[i][j]);
		}
	}
	return n;
}

Matrix * Matrix::activeDerivative()
{
	Matrix* n = new Matrix(rows, cols);
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j<cols; j++) {
			n->matrix[i][j] = sigmoidDerivative(matrix[i][j]);
		}
	}
	return n;
}

Matrix * Matrix::removeBottomLayer()
{
	Matrix* n = new Matrix(rows - 1, cols);
	for (int i = 0; i<n->rows; i++) {
		for (int j = 0; j<cols; j++) {
			n->matrix[i][j] = matrix[i][j];
		}
	}
	return n;
}


void Matrix::GradientDescentSubtract(Matrix* a, Matrix * delta, float lambda)
{
	//GradiendDescendAddition calculates matrix whitch should be substract to weights of neural net between layer a and next layer
	//a this layer
	//delta=dC/dz from next layer
	//lambda - learning rate

	//Update weights
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<cols - 1; j++)
			matrix[i][j] += (*a)(j,0) * (*delta)(i,0) * lambda;
	//Update bias
	for (int i = 0; i<rows; i++)
		matrix[i][cols - 1] += (*delta)(i,0) * lambda;
}


void Matrix::FinalGradientDescentWeightMatrix(Matrix* a, float mi, float lambda, int n)
{
	//mi - regularization parameter
	//lambda - learning rate
	//n - number of wighs in neural nerwork

	if (a->rows != rows || a->cols != cols)
	{
		std::cout << "ERROR: matrix dimensions dont match (Matrix::FinalGradientDescendWeightMatrix)" << std::endl;
		throw std::exception("matrix dimensions dont match (Matrix::FinalGradientDescendWeightMatrix)");
		return;
	}
	//--------------------------------------------
	//reguralization
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<cols - 1; j++)
			matrix[i][j] *= 1 - mi * lambda / (float)n;
	//--------------------------------------------
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<cols; j++)
			matrix[i][j] -= a->matrix[i][j];
}

Matrix * Matrix::clone()
{
	Matrix* clone = new Matrix(rows, cols);
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j<cols; j++) {
			clone->matrix[i][j] = matrix[i][j];
		}
	}
	return clone;
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
		delete [] matrix[i];
	delete [] matrix;
}

float & Matrix::operator()(int i, int j)
{
	return matrix[i][j];
}


std::ostream & operator<<(std::ostream & out, const Matrix & d)
{
	for (int i = 0; i < d.rows; i++)
	{
		for (int j = 0; j < d.cols; j++)
		{
			out << d.matrix[i][j] << " ";
		}
	}
	out << std::endl;
	return out;
}

std::istream & operator>>(std::istream & in, Matrix & d)
{
	for (int i = 0; i < d.rows; i++)
	{
		for (int j = 0; j < d.cols; j++)
		{
			in >> d.matrix[i][j];
		}
	}
	return in;
}
