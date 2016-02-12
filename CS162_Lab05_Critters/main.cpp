/*********************************************************************
** Program Filename: main.hpp
** Author: Giovanni Rosati
** email: rosatig@oregonstate.edu
** Date: 2016-02-05
** Description: Main cpp file for CS162_400 Lab 5
*********************************************************************/

//includes
#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include "critter.hpp"
#include "ant.hpp"
#include "doodlebug.hpp"

//usings
using std::cout;
using std::endl;
using std::cin;
using std::srand;
using std::rand;
using std::string;

void createArray(int, int);
void displayArray(Critter*[][20]);

int main()
{
	//initialize random number generator
	srand((unsigned)time(NULL));

	//initialize rounds to 0
	int roundsIn = 0;
	int roundsRemaining = 0;
	int gameTurnCount = 0;
	int exit = 0;

	//create an empty array of Critter pointers
	Critter* critterArray[20][20];

	//fill the array with NULL
	for (int i = 0; i < 20; i++)		//loop through each line
	{
		for (int j = 0; j < 20; j++)	//loop through each column
		{
			critterArray[i][j] = NULL;
		}
	}

	//randomly choose 105 cells, and place 100 ants and 5 doodlebugs
	int toggle = 1;// switch for testing
	if (toggle == 1)
	{
		int antCount = 0;
		int doodlebugCount = 0;

		for (int i = 0; i < 105; i++)
		{
			int row = rand() % (20);		//generates a random number from 0 to 19 for the row
			int col = rand() % (20);		//generates a random number from 0 to 19 for the column

			if (!critterArray[row][col])	//test if position is empty
			{
				if (antCount < 100)
				{
					Critter* temp = new Ant;
					critterArray[row][col] = temp;
					antCount += 1;
				}
				else if (doodlebugCount < 5)
				{
					Critter* temp = new Doodlebug;
					critterArray[row][col] = temp;
					doodlebugCount += 1;
				}
			}
			else
			{
				i -= 1;						//subtract from i because the position wasn't used
			}
		}
	}

	//non random array population scenarios for testing
	//place 100 ants in the top five rows
	//for (int i = 0; i < 5; i++)		//loop through each line
	//{
	//	for (int j = 0; j < 20; j++)	//loop through each column
	//	{
	//		Critter* temp = new Ant;
	//		critterArray[i][j] = temp;
	//	}
	//}

	//place 5 doodlebugs at the start of row 6
	//for (int i = 5; i < 6; i++)		//loop through each line
	//{
	//	for (int j = 0; j < 5; j++)	//loop through each column
	//	{
	//		Critter* temp = new Doodlebug;
	//		critterArray[i][j] = temp;
	//	}
	//}

	//testinf place  doodlebugs
	//{
	//	//doodlebugs for testing
	//	Critter* temp1 = new Doodlebug;
	//	critterArray[3][3] = temp1;
	//	Critter* temp2 = new Doodlebug;
	//	critterArray[3][16] = temp2;
	//	Critter* temp3 = new Doodlebug;
	//	critterArray[16][3] = temp3;
	//	Critter* temp4 = new Doodlebug;
	//	critterArray[16][16] = temp4;

	//	//ants for testing
	//	Critter* temp5 = new Ant;
	//	critterArray[0][0] = temp5;
	//	Critter* temp6 = new Ant;
	//	critterArray[0][19] = temp6;
	//}

	//cout << endl;
	//cout << endl;
	//cout << "Starting array:" << endl;
	//cout << endl;
	//cout << endl;

	//displayArray(critterArray);

	cout << endl;
	cout << endl;

	//display menu, provide exit option
	while (exit == 0)
	{
		if (roundsRemaining == 0)
		{
			cout << "How many rounds would you like to run? " << endl;
			cout << "(Enter 0 to quit)" << endl;
			cout << endl;
			cin >> roundsIn;
			roundsRemaining = roundsIn;
			if (roundsIn == 0) exit = 1;
			cout << endl;
			cout << endl;
		}

		for (int i = 0; i < roundsIn; i++)
		{
			if (roundsRemaining > 0)
			{
				//move doodlebugs
				//loop through the array and move only the doodlebugs that have not already moved this turn
				for (int i = 0; i < 20; i++)		//loop through each line
				{
					for (int j = 0; j < 20; j++)	//loop through each column
					{
						if (critterArray[i][j])		//determine if array position has a critter
						{
							if (critterArray[i][j]->getTurnCount() < gameTurnCount)  //skip if this critter has already moved
							{
								if (critterArray[i][j]->getSymbol() == "X")
								{
									critterArray[i][j]->move(critterArray, i, j);
								}
							}
						}
					}
				}

				//move ants
				//loop through the array and move only the ants
				for (int i = 0; i < 20; i++)		//loop through each line
				{
					for (int j = 0; j < 20; j++)	//loop through each column
					{
						if (critterArray[i][j]) //determine if array position has a critter
						{
							if (critterArray[i][j]->getTurnCount() < gameTurnCount)	//skip if this critter has already moved
							{
								//cout << "critter is present..." << endl;
								//cin.get();

								if (critterArray[i][j]->getSymbol() == "O") //test if this position has an ant
								{
									critterArray[i][j]->move(critterArray, i, j);
								}
							}
						}
					}
				}
				displayArray(critterArray);
				cout << endl;
				cout << endl;

				//update roundsRemaining & game turns counter
				gameTurnCount += 1;
				roundsRemaining--;
			}
		}
	}
	cout << endl;
	cout << "Goodbye...........";
	cin.get();

	cout << endl;
	cout << endl;
	cout << endl;
	return 0;
}

/*********************************************************************
** Function: displayArray
** Description: iterates through the entire array displaying
** X for a doodlebug, 0 for an ant, and a space if no critter is
** present, for each position.
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

void displayArray(Critter* arrayIn[][20])
{
	for (int i = 0; i < 20; i++)		//loop through each line
	{
		if (i < 10) cout << " Row " << i << ":  ";
		else cout << "Row " << i << ":  ";
		for (int j = 0; j < 20; j++)	//loop through each column
		{
			string output = " ";
			if (arrayIn[i][j])
			{
				output = arrayIn[i][j]->getSymbol();
			}
			cout << output;
			if (j == 19) cout << endl;
		}
	}
}