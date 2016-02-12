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

//variables for determining if any critter is in an adjacent cell, or out of bounds
int* critterCheck(Critter*[][20], int, int);	//function prototype
int critterPositions[4];						//array to hold values

//variables for determining which adjacent cells are vacant or out of bounds
int* emptyCellCheck2(Critter*[][20], int, int);
int* emtpyCellsNear2;
int emptyCellsArray2[4];

Ant::Ant()
{
	this->turnCount = 0;
}

Ant::~Ant()
{
	//cout << "ant deconstructor has run";
}

string Ant::getSymbol()
{
	return "O";
}

/*********************************************************************
** Function: move
** Description: moves an ant randomly, then breeds if ready.
** Pre-Conditions: none
** Post-Conditions: a new ant is created if current ant breeds
*********************************************************************/
void Ant::move(Critter* arrayIn[][20], int row, int col)
{
	//update turn count
	this->turnCount += 1;
	//generate a random number from 0-3
	int direction = rand() % (4);
	int* crittersNear;
	int done = 0;
	//test for an adjacent critter
	crittersNear = critterCheck(arrayIn, row, col);

	if ((row != 0) && (crittersNear[0] == 0) && (direction = 0))	//not at top row, no critter above, up is the move
	{
		//move ant
		arrayIn[row - 1][col] = arrayIn[row][col];
		//set old ant position to NULL
		arrayIn[row][col] = NULL;
		//check and place new ant in old location if ready to breed
		if ((arrayIn[row - 1][col]->getTurnCount() % 3) == 0)  //check if doodlebug has surviced 8 turns
		{
			Critter* temp = new Ant;
			arrayIn[row][col] = temp;
		}
		done = 1;
	}

	if ((col != 19) && (done != 1) && (crittersNear[1] == 0) && (direction = 1))  //not at right column, no critter right, right was the move
	{
		//move ant
		arrayIn[row][col + 1] = arrayIn[row][col];
		//set old ant position to NULL
		arrayIn[row][col] = NULL;
		//check and place new ant in old location if ready to breed
		if ((arrayIn[row][col + 1]->getTurnCount() % 3) == 0)  //check if doodlebug has surviced 8 turns
		{
			Critter* temp = new Ant;
			arrayIn[row][col] = temp;
		}
		done = 1;
	}

	if ((row != 19) && (done != 1) && (crittersNear[2] == 0) && (direction = 2))  //not at bottom row, no critter below, below was the move
	{
		//move ant
		arrayIn[row + 1][col] = arrayIn[row][col];
		//set old ant position to NULL
		arrayIn[row][col] = NULL;
		//check and place new ant in old location if ready to breed
		if ((arrayIn[row + 1][col]->getTurnCount() % 3) == 0)  //check if doodlebug has surviced 8 turns
		{
			Critter* temp = new Ant;
			arrayIn[row][col] = temp;
		}
		done = 1;
	}

	if ((col != 0) && (done != 1) && (crittersNear[3] == 0) && (direction = 3))  //not at first column, no critter left, left was the move
	{
		//move ant
		arrayIn[row][col - 1] = arrayIn[row][col];
		//set old ant position to NULL
		arrayIn[row][col] = NULL;
		//check and place new ant in old location if ready to breed
		if ((arrayIn[row][col - 1]->getTurnCount() % 3) == 0)  //check if doodlebug has surviced 8 turns
		{
			Critter* temp = new Ant;
			arrayIn[row][col] = temp;
		}
		done = 1;
	}
	//breed case if ant didn't move
	if (done = 0)	//where ant didn't change position
	{
		emtpyCellsNear2 = emptyCellCheck2(arrayIn, row, col);
		if (emtpyCellsNear2[0] == 1)
		{
			Critter* temp = new Ant;
			arrayIn[row - 1][col] = temp;
		}
		else if (emtpyCellsNear2[1] == 1)
		{
			Critter* temp = new Ant;
			arrayIn[row][col + 1] = temp;
		}
		else if (emtpyCellsNear2[2] == 1)
		{
			Critter* temp = new Ant;
			arrayIn[row + 1][col] = temp;
		}
		else if (emtpyCellsNear2[3] == 1)
		{
			Critter* temp = new Ant;
			arrayIn[row][col - 1] = temp;
		}
	}
}	//end of move function

/*********************************************************************
** Function: critterCheck
** Description: creates an array of four ints, each 0 or 1.
** 0 value = cell is empty or it is out of bounds
** 1 value = a critter is in that cell
** position 0 is for the cell above
** position 1 is for the cell to the right
** position 2 is for the cell below
** position 3 is for the cell to the left
** Pre-Conditions: none
** Post-Conditions: mone
*********************************************************************/
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

/*********************************************************************
** Function: emptyCellCheck2
** Description: creates an array of four ints, each 0 or 1.
** 0 value = a critter is in that cell or it is out of bounds
** 1 value = cell is empty
** position 0 is for the cell above
** position 1 is for the cell to the right
** position 2 is for the cell below
** position 3 is for the cell to the left
** Pre-Conditions: none
** Post-Conditions: mone
*********************************************************************/
int* emptyCellCheck2(Critter* arrayIn[][20], int row, int col)
{
	//make an array of int, set all values to zero

	for (int i = 0; i < 4; i++)
	{
		emptyCellsArray2[i] = 0;
	}

	//check for out of bounds as well
	//check cell above
	if (row != 0)  //check cell above only for rows 1 to 19
	{
		if (!(arrayIn[row - 1][col])) emptyCellsArray2[0] = 1;		//check for a critter
	}

	//check cell to the right
	if (col != 19) //don't check for column 19
	{
		if (!(arrayIn[row][col + 1])) emptyCellsArray2[1] = 1;	//check for a critter
	}

	//check cell below
	if (row != 19)  //check cell below only for rows 0 to 18
	{
		if (!(arrayIn[row + 1][col])) emptyCellsArray2[2] = 1;	//check for a critter
	}

	//check cell to the left
	if (col != 0) //don't check for column 0
	{
		if (!(arrayIn[row][col - 1])) emptyCellsArray2[3] = 1;//check for a critter
	}
	return emptyCellsArray2;
}