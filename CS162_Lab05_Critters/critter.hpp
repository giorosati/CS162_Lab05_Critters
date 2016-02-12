/*********************************************************************
** Program Filename: critter.hpp
** Author: Giovanni Rosati
** email: rosatig@oregonstate.edu
** Date: 2016-02-05
** Description: Shape class header file CS162_400 Lab 5
*********************************************************************/

#ifndef CRITTER_HPP
#define CRITTER_HPP

//includes

class Critter
{
protected:
	int turnCount;		//counter for number of turns experienced

public:
	Critter();							//default constructor
	~Critter();							//deconstructor
	virtual void move(Critter* arrayIn[][20], int x, int y);  //only implemented in the derived classes
	virtual std::string getSymbol();	//only implemented in the derived classes
	int getTurnCount();					//returns the # of turns the oject has existed
};

#endif