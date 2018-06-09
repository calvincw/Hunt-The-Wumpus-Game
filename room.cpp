///////////////////////////////////////////////////////////////////////
// Names		     : Diego Guzman
// Date				 : 11/28/2017
// Project			 : Hunt the Wumpus 
// Course			 : CSS 342
// File Description  : This file represent the room object in the 
//					   text-based game.
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "room.h"
#include <iostream>
using namespace std;
///////////////////Default Constructor///////////////////////////
Room::Room()
{
	roomNum = -1;
	pit = '\0';
	bat = '\0';
	monster = '\0';
	visited = false;
	row = -1;
	column = -1;
}
///////////////////Destructor////////////////////////
Room::~Room()
{
}

///////////////////Setters///////////////////////////
void Room::setRoomNum(int roomNum)
{
	this->roomNum = roomNum;
}
void Room::setPit(char pit)
{
	this->pit = pit;
}
void Room::setBat(char bat)
{
	this->bat = bat;
}
void Room::setMonster(char monster)
{
	this->monster = monster;
}
void Room::setAsVisited(char visited)
{
	this->visited = visited;
}
void Room::setPlayerSymbol(char symbol)
{
	this->playerSymbol = symbol;
}
void Room::setRow(int row)
{
	this->row = row;
}
void Room::setColumn(int column)
{
	this->column = column;
}
///////////////////getters///////////////////////////
int Room::getRoomNum() const
{
	return roomNum;
}
char Room::getPit() const
{
	return pit;
}
char Room::getBat() const
{
	return bat;
}
char Room::getMonster() const
{
	return monster;
}
char Room::getVisited() const
{
	return visited;
}
char Room::getPlayerSymbol() const
{
	return playerSymbol;
}
int Room::getRow() const
{
	return row;
}
int Room::getColumn() const
{
	return column;
}
bool Room::containsBat(char bat1)
{
	if (this->bat == bat1) 
	{
		return true;
	}
	return false;
}
///////////////////output operator overload///////////
ostream & operator<<(ostream & output, const Room & rhs)
{
	output << "Room Number:"<<rhs.getRoomNum()<<endl;

	return output;
}
