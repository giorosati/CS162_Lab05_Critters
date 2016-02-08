/*********************************************************************
** Program Filename: doodlebug.cpp
** Author: Giovanni Rosati
** email: rosatig@oregonstate.edu
** Date: 2016-02-05
** Description: Doodlebug class implementation file CS162_400 Lab 5
*********************************************************************/

#include <cstdlib>
#include <iostream>
#include "doodlebug.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::srand;
using std::rand;
using std::string;

int* antCheck(Critter*[][20], int, int);
int antPositions[4];

Doodlebug::Doodlebug()
{
	this->turnCount = 0;
}

Doodlebug::~Doodlebug()
{
	//cout << "doodlebug deconstructor has run";
}

void Doodlebug::move(Critter* arrayIn[][20], int row, int col)
{
	//update turn count
	this->turnCount += 1;
	//generate a random number from 1-4
	int direction = rand() % (4) + 1;
	int* antsNear;
	int done = 0;
	//test for an adjacent ant
	antsNear = antCheck(arrayIn, row, col);
	if (antsNear[0] == 1)	//if there is an ant above
	{
		//delete the ant that was there
		delete arrayIn[row - 1][col];
		//move doodlebug
		arrayIn[row - 1][col] = arrayIn[row][col];
		//set doodlebug old position to NULL
		arrayIn[row][col] = NULL;
		done = 1;
	}

	if (done != 1)
	{
		if (antsNear[1] == 1)	//if there is an ant to the right
		{
			//delete the ant that was there
			delete arrayIn[row][col + 1];
			//move doodlebug
			arrayIn[row][col + 1] = arrayIn[row][col];
			//set doodlebug old position to NULL
			arrayIn[row][col] = NULL;
			done = 1;
		}
	}

	if (done != 1)
	{
		if (antsNear[2] == 1)	//if there is an ant below
		{
			//delete the ant that was there
			delete arrayIn[row + 1][col];
			//move doodlebug
			arrayIn[row + 1][col] = arrayIn[row][col];
			//set doodlebug old position to NULL
			arrayIn[row][col] = NULL;
			done = 1;
		}
	}

	if (done != 1)
	{
		if (antsNear[3] == 1)	//if there is an ant to the left
		{
			//delete the ant that was there
			delete arrayIn[row][col - 1];
			//move doodlebug
			arrayIn[row][col - 1] = arrayIn[row][col];
			//set doodlebug old position to NULL
			arrayIn[row][col] = NULL;
			done = 1;
		}
	}
}

//void breed()
//{
//	cout << "doodlebug breed has been called.";
//}

string Doodlebug::getSymbol()
{
	return "X";
}

//returns an array
int* antCheck(Critter* arrayIn[][20], int row, int col)
{
	//make an array of int, set all values to zero

	for (int i = 0; i < 4; i++)
	{
		antPositions[i] = 0;
	}

	//check for out of bounds as well
	//check cell above
	if (row != 0)  //check cell above only for rows 1 to 19
	{
		if (arrayIn[row - 1][col]) //check for a critter
		{
			if (arrayIn[row - 1][col]->getSymbol() == "O") antPositions[0] = 1;  //check for an ant
		}
	}

	//check cell to the right
	if (col != 19) //don't check for column 19
	{
		if (arrayIn[row][col + 1]) //check for a critter
		{
			if (arrayIn[row][col + 1]->getSymbol() == "O") antPositions[1] = 1;  //check for an ant
		}
	}

	//check cell below
	if (row != 19)  //check cell below only for rows 0 to 18
	{
		if (arrayIn[row + 1][col]) //check for a critter
		{
			if (arrayIn[row + 1][col]->getSymbol() == "O") antPositions[2] = 1;  //check for an ant
		}
	}

	//check cell to the left
	if (col != 0) //don't check for column 0
	{
		if (arrayIn[row][col - 1]) //check for a critter
		{
			if (arrayIn[row][col - 1]->getSymbol() == "O") antPositions[3] = 1;  //check for an ant
		}
	}
	return antPositions;
}