#include "NeuralNet.h"

NeuralNet::NeuralNet(int n_layer,int* l): n_layer(n_layer)
{
	//new architecture
	layer = new int[n_layer];
	for (int i = 0; i < n_layer; i++)
		layer[i] = l[i];

	weights = new Matrix*[n_layer - 1];
	for (int i = 0; i < n_layer - 1; i++)
	{
		weights[i] = new Matrix(layer[i+1], layer[i]+1);
		weights[i]->randomize();
	}
		
}

NeuralNet::NeuralNet(NeuralNet & d) :  n_layer(d.n_layer)
{
	layer = new int[n_layer];
	for (int i = 0; i < n_layer; i++)
		layer[i] = d.layer[i];
	weights = new Matrix*[n_layer - 1];
	for (int i = 0; i < n_layer - 1; i++)
		weights[i] = d.weights[i]->clone();
}



void NeuralNet::GradientDescent(int m, int*board[], int n1, float* y[], int n2, float lambda,float mi)
{
	
	//m - number of trening situations
	//board - vector of inputs
	//n1 - size of board
	//y - vector of outputs
	//n2 - size of output
	//lambda - learning rate
	//mi - regulation rate

	/*
	//Create empty matrixes for every weigh layer
	whi = new Matrix(hNodes, iNodes + 1);
	whh = new Matrix(hNodes, hNodes + 1);
	woh = new Matrix(oNodes, hNodes + 1);
	*/

	//New architecture
	//w[i] - matrix corresponding to weight[i]
	Matrix** w = new Matrix*[n_layer - 1];
	for (int i = 0; i<n_layer - 1; i++)
		w[i] = new Matrix(layer[i + 1], layer[i] + 1);

	//Calculate dC/dwi for every traning set
	Matrix** zl=nullptr;
	Matrix** al=nullptr;
	Matrix** delta; 
	for (int i = 0; i < m; i++)
	{
		
		//get al,zl
		zl_al(al, zl, board[i],n1);
		//get delta
		delta = GradientDescent_1(zl, al[n_layer - 1], y[i],n2);
		for (int j = 0; j<n_layer - 1; j++)
		{
			//apply delta to matixes
			w[j]->GradientDescentSubtract(al[j], delta[j], lambda / (float)m);
			delete delta[j];
			delete al[j];
		}
		//clean rest
		delete al[n_layer - 1];
		delete[] al;
		delete[] delta;
		delta = nullptr;
		al = nullptr;
	}
	int n = 0;
	for (int i = 0; i < n_layer; i++)
		n += layer[i];
	for (int j = 0; j<n_layer - 1; j++)
	{
		weights[j]->FinalGradientDescentWeightMatrix(w[j],mi,lambda,n);			//mi - regularization parameter, n - number of weights in neural network
		delete w[j];
	}
}


void NeuralNet::zl_al(Matrix** &al, Matrix** &zl, int* board,int n)
{
	//zl_al calculates layers of neural network before activation and layers after activation while calculating training example board
	//al - empty pointer where function should put layers after activation (size n_layer)
	//zl - empty pointer where function should put layers before activation	(size n_layer-1) 
	//board - training example (input)
	//n - sizeof board
	//al[i+1]=zl[i]->activation()

	if (al || zl)
		std::cout << "Error: overriding old data, memory loss (zl_al)" << std::endl;

	zl = new Matrix*[n_layer - 1];
	al = new Matrix*[n_layer];
	al[0] = Matrix::singleColumnMatrixFromArray(board,n);              
	//forward propagation
	for (int i = 0; i<n_layer - 1; i++)
	{
		
		Matrix* withBias = al[i]->addBias();
		zl[i] = weights[i]->dot(withBias);
		delete withBias;
		al[i + 1] = zl[i]->activate();
	}
}


Matrix** NeuralNet::GradientDescent_1(Matrix** &zl, Matrix* a, float* y, int n2)
{
	//GradiendDescent_1 calculates vector of matrixes which represents derivative of error with respect to weights of neural network
	//zl - layers of network while calculating trening example before cativation, !! zl will by deleted !!
	//a - output layer of neural network while calculating training example
	//y - correct answer of that example
	//n2 - size of y



	//Calculate delta - derivative of error function with respect to zl
	Matrix** delta = new Matrix*[n_layer - 1];

	//-------------------------------------------------------
	/*
	//mean square error

	//Calculate derivative of error function with respect to a
	float* tmp = a->toArray();
	Matrix* dCdaL = DeltaL(tmp, y);
	delete tmp;

	//delta[L] = dCaL.*fi'(z[L])
	delta[n_layer - 2] = dCdaL->hadamard(zl[n_layer - 2]->activeDerivative());
	*/

	//-------------------------------------------------------
	//cross entropy
	delta[n_layer - 2] = new Matrix(n2, 1);
	for(int i=0;i<n2;i++)
		(*delta[n_layer - 2])(i,0) = (*a)(i, 0) - y[i]; 						

	//-------------------------------------------------------

	delete zl[n_layer - 2];

	//back propagation
	for (int i = n_layer - 3; i >= 0; i++)
	{
		//delta[l] = (w[l+1]*delta[l+1]).*fi'(z[l])

		Matrix* w_T = weights[i]->transpose();
		Matrix* tmp = w_T->dot(delta[i + 1]);
		Matrix* tmpBias = tmp->deleteBias();
		Matrix* tmp2 = zl[i]->activeDerivative();
		delta[i] = tmpBias->hadamard(tmp2);
		delete w_T; delete tmp; delete tmpBias; delete tmp2; delete zl[i];
	}
	delete[] zl;
	zl = nullptr;
	return delta;
}


Matrix* NeuralNet::DeltaL(float* a, float* y) //(Matrix * a, Matrix * y)
{
	//DeltaL calculates derivative of error function with respect to output layer of neural net
	//a - calculated answer !! delete a !!
	//y - correct answer	!! delete y !!

	/*
	//mean square error
	a[0] -= y[0];
	Matrix* tmp = Matrix::singleColumnMatrixFromArray(a, 1);
	delete a; delete y;
	return tmp;
	*/

	//cross entropy	(useless)
	a[0] = y[0] / a[0] - (1.f - y[0]) / (1.f - a[0]); //=(y[0]-a[0])/fi'(z)
	Matrix* tmp = Matrix::singleColumnMatrixFromArray(a, 1);
	delete a; delete y;
	return tmp;
}




float * NeuralNet::output(float * inputsArr, int l)
{
	Matrix* inputs = Matrix::singleColumnMatrixFromArray(inputsArr, l);
	for (int i = 0; i < n_layer - 1; i++)
	{
		Matrix* inputsBias = inputs->addBias();
		Matrix* nextInputs = weights[i]->dot(inputsBias);
		delete inputs;
		inputs = nextInputs->activate();
		delete inputsBias;
		delete nextInputs;
	}
	float* wyn = (*inputs).toArray();
	delete inputs;
	return wyn;
}


NeuralNet * NeuralNet::clone()
{
	//xp
	NeuralNet* clone = new NeuralNet(*this);

	return clone;
}

NeuralNet::~NeuralNet()
{
	for (int i = 0; i < n_layer - 1; i++)
		delete weights[i];
	delete[] weights;
	delete[] layer;
}

std::ostream & operator<<(std::ostream & out,const NeuralNet& d)
{
	//idk
	return out;
}

std::istream & operator>>(std::istream & in, NeuralNet & d)
{
	//idk
	return in;
}

