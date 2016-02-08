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
protected:

public:
	Doodlebug();				//default constructor
	~Doodlebug();				//deconstructor
	void move(Critter* arrayIn[][20], int row, int col);
	//	void breed();
	std::string getSymbol();
};

#endif