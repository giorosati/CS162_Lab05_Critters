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

//variables for determining if an ant is in an adjacent cell
int* antCheck(Critter*[][20], int, int);
int antPositions[4];

//variables for determining if any critter is in an adjacent cell, or out of bounds
int* critterCheck2(Critter*[][20], int, int);
int* crittersNear;
int critterPositions2[4];

//variables for determining which adjacent cells are vacant or out of bounds
int* emptyCellCheck(Critter*[][20], int, int);
int* emtpyCellsNear;
int emptyCellsArray[4];

Doodlebug::Doodlebug()
{
	this->turnCount = 0;
	this->turnsSinceEat = 0;
}

Doodlebug::~Doodlebug()
{
	//cout << "doodlebug deconstructor has run";
}

/*********************************************************************
** Function: move
** Description: moves a doodlebug to eat an adjacent ant, or
** moves a doodlebug randomly, then breeds if ready, then dies if ready
** Parameters: 20 x 20 array of int pointers to critters, int for current
** row position, int for current column position.
** Pre-Conditions: srand is used to seed the rand function, main has
** confimed current row & column contains a doodlebug.
** Post-Conditions: new doodlebug placed in array if breed happenned,
** doodlebug deleted if death occurred, and an ant was deleted if it
** was eaten.
*********************************************************************/
void Doodlebug::move(Critter* arrayIn[][20], int row, int col)
{
	//update turn count
	this->turnCount += 1;
	this->turnsSinceEat += 1;

	//generate a random number from 0-3
	int direction = rand() % (4);
	//direction = 0;

	//cout << "direction: " << direction << endl;
	//cin.get();

	int* antsNear;
	int done = 0;
	int moveDirection = 4; //set default to 4, which represents the doodlebug not did change position

	//test for an adjacent ant
	//create an array for ants in the adjacent 4 cells
	antsNear = antCheck(arrayIn, row, col);

	//move phase 1: move and eat an ant, in this order of preference: top, right, bottom, left

	//move if an ant is above
	if ((row != 0) && (antsNear[0] == 1))	//if there is an ant above, but skip for row 0
	{
		//delete the ant that was there
		delete arrayIn[row - 1][col];
		turnsSinceEat = 0;	//reset turns elapsed since last ate an ant
		//move doodlebug
		arrayIn[row - 1][col] = arrayIn[row][col];
		//set doodlebug old position to NULL
		arrayIn[row][col] = NULL;
		moveDirection = 0;
		done = 1;
	}

	if (done != 1)
	{
		//move if an ant is right
		if ((col != 19) && (antsNear[1] == 1))	//if there is an ant to the right, but skip for column 19
		{
			//delete the ant that was there
			delete arrayIn[row][col + 1];
			turnsSinceEat = 0;	//reset turns elapsed since last ate an ant
			//move doodlebug
			arrayIn[row][col + 1] = arrayIn[row][col];
			//set doodlebug old position to NULL
			arrayIn[row][col] = NULL;
			moveDirection = 1;
			done = 1;
		}
	}

	if (done != 1)
	{
		//move if ant below
		if ((row != 19) && (antsNear[2] == 1))	//if there is an ant below, skip for row 19
		{
			//delete the ant that was there
			delete arrayIn[row + 1][col];
			turnsSinceEat = 0;	//reset turns elapsed since last ate an ant
			//move doodlebug
			arrayIn[row + 1][col] = arrayIn[row][col];
			//set doodlebug old position to NULL
			arrayIn[row][col] = NULL;
			moveDirection = 2;
			done = 1;
		}
	}

	if (done != 1)
	{
		//move if ant left
		if ((col != 0) && (antsNear[3] == 1))	//if there is an ant to the left, skip for column 0
		{
			//delete the ant that was there
			delete arrayIn[row][col - 1];
			turnsSinceEat = 0;	//reset turns elapsed since last ate an ant
			//move doodlebug
			arrayIn[row][col - 1] = arrayIn[row][col];
			//set doodlebug old position to NULL
			arrayIn[row][col] = NULL;
			moveDirection = 3;
			done = 1;
		}
	}   //end of move phase 1

	//move phase 2: to move doodlebugs that did not eat an ant this turn
	if (done != 1)
	{
		//test for an adjacent critter
		//create adjacent critter array
		crittersNear = critterCheck2(arrayIn, row, col);

		if ((row != 0) && (crittersNear[0] == 0) && (direction = 0))	//not at top row, no critter above, up is the move
		{
			//move up
			arrayIn[row - 1][col] = arrayIn[row][col];
			//set old position to NULL
			arrayIn[row][col] = NULL;
			moveDirection = 0;
			done = 1;
		}

		if ((col != 19) && (done != 1) && (crittersNear[1] == 0) && (direction = 1))  //not at right column, no critter right, right was the move
		{
			//move right
			arrayIn[row][col + 1] = arrayIn[row][col];
			//set old position to NULL
			arrayIn[row][col] = NULL;
			moveDirection = 1;
			done = 1;
		}

		if ((row != 19) && (done != 1) && (crittersNear[2] == 0) && (direction = 2))  //not at bottom row, no critter below, below was the move
		{
			//move down
			arrayIn[row + 1][col] = arrayIn[row][col];
			//set old position to NULL
			arrayIn[row][col] = NULL;
			moveDirection = 2;
			done = 1;
		}

		if ((col != 0) && (done != 1) && (crittersNear[3] == 0) && (direction = 3))  //not at first column, no critter left, left was the move
		{
			//move left
			arrayIn[row][col - 1] = arrayIn[row][col];
			//set old position to NULL
			arrayIn[row][col] = NULL;
			moveDirection = 3;
			done = 1;
		}
	}  //end of move phase 2

	//breed and die section  -  doodlebug dies at THE END of the third time step...
	switch (moveDirection)
	{
	case 0:  //move was up, place new doodlebug in prior position
	{
		if ((arrayIn[row - 1][col]->getTurnCount() % 8) == 0)  //check if doodlebug has surviced 8 turns
		{
			Critter* temp = new Doodlebug;
			arrayIn[row][col] = temp;
		}
		if (turnsSinceEat == 3)
		{
			delete arrayIn[row - 1][col];	//delete the Doodlebug
			arrayIn[row - 1][col] = NULL;	//set doodlebug's former position to NULL
		}
		break;
	}
	case 1:  //move was to the right
	{
		if ((arrayIn[row][col + 1]->getTurnCount() % 8) == 0)  //check if doodlebug has surviced 8 turns
		{
			Critter* temp = new Doodlebug;
			arrayIn[row][col] = temp;
		}
		if (turnsSinceEat == 3)
		{
			delete arrayIn[row][col + 1];	//delete the Doodlebug
			arrayIn[row][col + 1] = NULL;	//set doodlebug's former position to NULL
		}
		break;
	}
	case 2:	//move was down
	{
		if ((arrayIn[row + 1][col]->getTurnCount() % 8) == 0)  //check if doodlebug has surviced 8 turns
		{
			Critter* temp = new Doodlebug;
			arrayIn[row][col] = temp;
		}
		if (turnsSinceEat == 3)
		{
			delete arrayIn[row + 1][col];	//delete the Doodlebug
			arrayIn[row + 1][col] = NULL;	//set doodlebug's former position to NULL
		}
		break;
	}
	case 3: //move was to the left
	{
		if ((arrayIn[row][col - 1]->getTurnCount() % 8) == 0)  //check if doodlebug has surviced 8 turns
		{
			Critter* temp = new Doodlebug;
			arrayIn[row][col] = temp;
		}
		if (turnsSinceEat == 3)
		{
			delete arrayIn[row][col - 1];	//delete the Doodlebug
			arrayIn[row][col - 1] = NULL;	//set doodlebug's former position to NULL
		}
		break;
	}
	case 4:  //where the doodlebug never changed position
	{
		emtpyCellsNear = emptyCellCheck(arrayIn, row, col);    //array positions: 0 = up, 1 = right, 2 = down, 3 = left
		if (emtpyCellsNear[0] == 1)
		{
			Critter* temp = new Doodlebug;
			arrayIn[row - 1][col] = temp;
		}
		else if (emtpyCellsNear[1] == 1)
		{
			Critter* temp = new Doodlebug;
			arrayIn[row][col + 1] = temp;
		}
		else if (emtpyCellsNear[2] == 1)
		{
			Critter* temp = new Doodlebug;
			arrayIn[row + 1][col] = temp;
		}
		else if (emtpyCellsNear[3] == 1)
		{
			Critter* temp = new Doodlebug;
			arrayIn[row][col - 1] = temp;
		}
		if (turnsSinceEat == 3)
		{
			delete arrayIn[row][col];	//delete the Doodlebug
			arrayIn[row][col] = NULL;	//set doodlebug's former position to NULL
		}
	}
	}	//end of breed switch
}      //end of move

string Doodlebug::getSymbol()
{
	return "X";
}

/*********************************************************************
** Function: antCheck
** Description: creates an array of four ints, each 0 or 1.
** 0 value = no ant in that position
** 1 value = ant in that position
** position 0 is for the cell above
** position 1 is for the cell to the right
** position 2 is for the cell below
** position 3 is for the cell to the left
** Pre-Conditions: none
** Post-Conditions: mone
*********************************************************************/
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

/*********************************************************************
** Function: critterCheck2
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
int* critterCheck2(Critter* arrayIn[][20], int row, int col)
{
	//make an array of int, set all values to zero

	for (int i = 0; i < 4; i++)
	{
		critterPositions2[i] = 0;
	}

	//check for out of bounds as well
	//check cell above
	if (row != 0)  //check cell above only for rows 1 to 19
	{
		if (arrayIn[row - 1][col]) critterPositions2[0] = 1;		//check for a critter
	}

	//check cell to the right
	if (col != 19) //don't check for column 19
	{
		if (arrayIn[row][col + 1]) critterPositions2[1] = 1;	//check for a critter
	}

	//check cell below
	if (row != 19)  //check cell below only for rows 0 to 18
	{
		if (arrayIn[row + 1][col]) critterPositions2[2] = 1;	//check for a critter
	}

	//check cell to the left
	if (col != 0) //don't check for column 0
	{
		if (arrayIn[row][col - 1]) critterPositions2[3] = 1;//check for a critter
	}
	return critterPositions2;
}

/*********************************************************************
** Function: emptyCellCheck
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
int* emptyCellCheck(Critter* arrayIn[][20], int row, int col)
{
	//make an array of int, set all values to zero

	for (int i = 0; i < 4; i++)
	{
		emptyCellsArray[i] = 0;
	}

	//check for out of bounds as well
	//check cell above
	if (row != 0)  //check cell above only for rows 1 to 19
	{
		if (!(arrayIn[row - 1][col])) emptyCellsArray[0] = 1;		//check for a critter
	}

	//check cell to the right
	if (col != 19) //don't check for column 19
	{
		if (!(arrayIn[row][col + 1])) emptyCellsArray[1] = 1;	//check for a critter
	}

	//check cell below
	if (row != 19)  //check cell below only for rows 0 to 18
	{
		if (!(arrayIn[row + 1][col])) emptyCellsArray[2] = 1;	//check for a critter
	}

	//check cell to the left
	if (col != 0) //don't check for column 0
	{
		if (!(arrayIn[row][col - 1])) emptyCellsArray[3] = 1;//check for a critter
	}
	return emptyCellsArray;
}