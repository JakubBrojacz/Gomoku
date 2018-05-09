#pragma once
#include <random>

const int WINDOWX = 1000;
const int WINDOWY = 800;
const int BOARDSIZE = 15;

const int INPUTNODES = BOARDSIZE* BOARDSIZE;
const int OUTPUTNODES = BOARDSIZE* BOARDSIZE;
const int HIDDENNODES = BOARDSIZE* BOARDSIZE*2;

const float DELTATIME = 0.1; //refreshing time

const int SQUARESIZE = 20;



double GaussRandom();

#define SAMESEED