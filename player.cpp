///////////////////////////////////////////////////////////////////////
// Names		     : Diego Guzman
// Date				 : 11/28/2017
// Project			 : Hunt the Wumpus 
// Course			 : CSS 342
// File Description  : This file represents the player object in the 
//					   text-based game.
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Player.h"
#include <iostream>

using namespace std;
///////////////////Default Constructor///////////////////////////
Player::Player() 
{
	initialR = 0;
	initialC = 0;
}
///////////////////Constructor//////////////////////////////////
Player::Player(int r, int c) 
{
	this->initialR = r;
	this->initialC = c;
	this->currentR = r;
	this->currentC = c;
}
/////////Sets the current row location////////////////
void Player::setCurrentR(int r)
{
	this->currentR = r;
}
/////////Sets the current column location///////////
void Player::setCurrentC(int c) 
{
	this->currentC = c;
}
/////////Sets the object to a new location////////////////
void Player::setNewLocation(int r, int c)
{
	this->currentR = r;
	this->currentC = c;
}
/////////////Move the object north/////////////////////
Player Player::goNorth() // decreases current row
{
	Player newPlayer(currentR - 1, currentC);
	return newPlayer;
}
/////////////Move the object east/////////////////////
Player Player::goEast()	// increases current Column
{
	Player newPlayer(currentR, currentC + 1);
	return newPlayer;
}
/////////////Move the object south///////////////////
Player Player::goSouth() // increases current row
{
	Player newPlayer(currentR + 1, currentC);
	return newPlayer;
}
/////////////Move the object west/////////////////////
Player Player::goWest() // decreases current column
{
	Player newPlayer(currentR, currentC - 1);
	return newPlayer;
}
///////////////////output operator overload///////////
ostream & operator<<(ostream & output, const Player & rhs)
{
	output << "[" << rhs.currentR << "," << rhs.currentC << "]";
	return output;
}
///////////////////Destructor////////////////////////
Player::~Player()
{
}
