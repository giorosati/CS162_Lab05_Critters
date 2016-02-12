/*********************************************************************
** Program Filename: ant.hpp
** Author: Giovanni Rosati
** email: rosatig@oregonstate.edu
** Date: 2016-02-05
** Description: Ant class header file CS162_400 Lab 5
*********************************************************************/

#ifndef ANT_HPP
#define ANT_HPP

//includes
#include "critter.hpp"

class Ant : public Critter
{
protected:

public:
	Ant();				//default constructor
	~Ant();				//deconstructor

	/*********************************************************************
	** Function: move
	** Description: moves an ant randomly, then breeds if ready.
	** Pre-Conditions: none
	** Post-Conditions: a new ant is created if current ant breeds
	*********************************************************************/
	void move(Critter* arrayIn[][20], int x, int y);

	std::string getSymbol();	//returns 0
};

#endif