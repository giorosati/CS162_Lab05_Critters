/*********************************************************************
** Program Filename: ant.cpp
** Author: Giovanni Rosati
** email: rosatig@oregonstate.edu
** Date: 2016-02-05
** Description: Ant class implementation file CS162_400 Lab 5
*********************************************************************/

#include <cstdlib>
#include <iostream>
#include "ant.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::srand;
using std::rand;
using std::string;

int* critterCheck(Critter*[][20], int, int);
int critterPositions[4];

Ant::Ant()
{
	this->turnCount = 0;
}

Ant::~Ant()
{
	//cout << "ant deconstructor has run";
}

void Ant::move(Critter* arrayIn[][20], int row, int col)
{
	//update turn count
	this->turnCount += 1;
	//generate a random number from 1-4
	int direction = rand() % (4) + 1;
	int* crittersNear;
	int done = 0;
	//test for an adjacent critter
	crittersNear = critterCheck(arrayIn, row, col);

	if ((row != 0) && (crittersNear[0] == 0) && (direction = 1))	//not at top row, no critter above, up is the move
	{
		//move ant
		arrayIn[row - 1][col] = arrayIn[row][col];
		//set old ant position to NULL
		arrayIn[row][col] = NULL;
		done = 1;
	}

	if ((col != 19) && (done != 1) && (crittersNear[1] == 0) && (direction = 2))  //not at right column, no critter right, right was the move
	{
		//move ant
		arrayIn[row][col + 1] = arrayIn[row][col];
		//set old ant position to NULL
		arrayIn[row][col] = NULL;
		done = 1;
	}

	if ((row != 19) && (done != 1) && (crittersNear[2] == 0) && (direction = 3))  //not at bottom row, no critter below, below was the move
	{
		//move ant
		arrayIn[row + 1][col] = arrayIn[row][col];
		//set old ant position to NULL
		arrayIn[row][col] = NULL;
		done = 1;
	}

	if ((col != 0) && (done != 1) && (crittersNear[3] == 0) && (direction = 4))  //not at first column, no critter left, left was the move
	{
		//move ant
		arrayIn[row][col - 1] = arrayIn[row][col];
		//set old ant position to NULL
		arrayIn[row][col] = NULL;
		done = 1;
	}
}

//void breed()
//{
//	cout << "Ant breed has been called.";
//}

string Ant::getSymbol()
{
	return "O";
}

//returns an array
int* critterCheck(Critter* arrayIn[][20], int row, int col)
{
	//make an array of int, set all values to zero

	for (int i = 0; i < 4; i++)
	{
		critterPositions[i] = 0;
	}

	//check for out of bounds as well
	//check cell above
	if (row != 0)  //check cell above only for rows 1 to 19
	{
		if (arrayIn[row - 1][col]) critterPositions[0] = 1;		//check for a critter
	}

	//check cell to the right
	if (col != 19) //don't check for column 19
	{
		if (arrayIn[row][col + 1]) critterPositions[1] = 1;	//check for a critter
	}

	//check cell below
	if (row != 19)  //check cell below only for rows 0 to 18
	{
		if (arrayIn[row + 1][col]) critterPositions[2] = 1;	//check for a critter
	}

	//check cell to the left
	if (col != 0) //don't check for column 0
	{
		if (arrayIn[row][col - 1]) critterPositions[3] = 1;//check for a critter
	}
	return critterPositions;
}