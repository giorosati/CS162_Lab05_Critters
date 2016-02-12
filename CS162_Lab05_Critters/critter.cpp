/*********************************************************************
** Program Filename: critter.cpp
** Author: Giovanni Rosati
** email: rosatig@oregonstate.edu
** Date: 2016-02-05
** Description: Critter class implementation file CS162_400 Lab 5
*********************************************************************/

#include <cstdlib>
#include <iostream>
#include "critter.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::srand;
using std::rand;
using std::string;

Critter::Critter()
{
	this->turnCount = 0;
}

Critter::~Critter()
{
	//cout << "critter deconstructor has run";
}

void Critter::move(Critter* arrayIn[][20], int x, int y)
{
	//cout << "critter move has been called.";
}

//void breed(Critter&);

string Critter::getSymbol()	//to be overridden by derived class
{
	return "C";
};

int Critter::getTurnCount()
{
	return turnCount;
}