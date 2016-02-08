/*********************************************************************
** Program Filename: main.hpp
** Author: Giovanni Rosati
** email: rosatig@oregonstate.edu
** Date: 2016-02-05
** Description: Main cpp file for CS162_400 Lab 5
*********************************************************************/

//includes
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

	//initialize roudns to 0
	int roundsIn = 0;
	//ask for initial rounds
	cout << "How many rounds would you like to run? " << endl;
	cin >> roundsIn;
	int roundsRemaining = roundsIn;

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
	/*for (int i = 0; i < 105)
	{
		int result = rand() % () + 1
	}*/

	//non random array population for testing
	//place 100 ants in the top five rows
	for (int i = 0; i < 5; i++)		//loop through each line
	{
		for (int j = 0; j < 20; j++)	//loop through each column
		{
			Critter* temp = new Ant;
			critterArray[i][j] = temp;
		}
	}

	//place 5 doodlebugs at the start of row 6
	for (int i = 5; i < 6; i++)		//loop through each line
	{
		for (int j = 0; j < 5; j++)	//loop through each column
		{
			Critter* temp = new Doodlebug;
			critterArray[i][j] = temp;
		}
	}

	displayArray(critterArray);
	//cout << "rounds remaining is: " << roundsRemaining << endl;
	//cin.get();

	//display menu, provide exit option
	//if (roundsRemaining = 0)
	//{
	//	cout << "How many rounds would you like to run? " << endl;
	//	cout << "(Enter 0 to quit)" << endl;
	//	cout << endl;
	//	cin >> roundsIn;
	//	roundsRemaining = roundsIn;
	//}

	if (roundsRemaining > 0)
	{
		//cout << "rounds remaining is: " << roundsRemaining << endl;
		//cin.get();

		for (int i = 0; i < roundsIn; i++)
		{
			//move doodlebugs
			//loop through the array and move only the doodlebugs
			for (int i = 0; i < 20; i++)		//loop through each line
			{
				for (int j = 0; j < 20; j++)	//loop through each column
				{
					if (critterArray[i][j]) //determine if array position has a critter
					{
						if (critterArray[i][j]->getSymbol() == "X")
						{
							critterArray[i][j]->move(critterArray, i, j);
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
						if (critterArray[i][j]->getSymbol() == "0") //test if this position has an ant
						{
							critterArray[i][j]->move(critterArray, i, j);
						}
					}
				}
			}

			displayArray(critterArray);
			cin.get();

			//display updated grid

			//update roundsRemaining
			roundsRemaining--;
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

void displayArray(Critter* arrayIn[][20])
{
	for (int i = 0; i < 20; i++)		//loop through each line
	{
		for (int j = 0; j < 20; j++)	//loop through each column
		{
			string output = " ";
			if (arrayIn[i][j])
			{
				output = arrayIn[i][j]->getSymbol();
				//cout << "Output is: " << output;
				//cin.get();
			}
			cout << output;
			if (j == 19) cout << endl;
		}
	}
}