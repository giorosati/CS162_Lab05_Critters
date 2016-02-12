/*********************************************************************
** Program Filename: doodlebug.hpp
** Author: Giovanni Rosati
** email: rosatig@oregonstate.edu
** Date: 2016-02-05
** Description: Doodlebug class header file CS162_400 Lab 5
*********************************************************************/

#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

//includes
#include "critter.hpp"

class Doodlebug : public Critter
{
private:
	int turnsSinceEat;	//counter to track turns since last eating an ant
protected:

public:
	Doodlebug();				//default constructor
	~Doodlebug();				//deconstructor

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
	void move(Critter* arrayIn[][20], int row, int col);

	std::string getSymbol();	//returns X
};

#endif