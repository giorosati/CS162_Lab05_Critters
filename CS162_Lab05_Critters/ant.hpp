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
	void move(Critter* arrayIn[][20], int x, int y);
	//	void breed();
	std::string getSymbol();
};

#endif