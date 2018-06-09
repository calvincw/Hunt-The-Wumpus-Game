#pragma once
///////////////////////////////////////////////////////////////////////
// Names		     : Diego Guzman
// Date				 : 11/28/2017
// Project			 : Hunt the Wumpus 
// Course			 : CSS 342
// File Description  : This is the header file for the room object
///////////////////////////////////////////////////////////////////////
#ifndef ROOM_H
#define ROOM_H

#include <iostream>

class Room
{
	public:
		///////////////////Destructor////////////////////////
		~Room();
		///////////////////Constructor///////////////////////
		Room();
		///////////////////Setters///////////////////////////
		void setRoomNum(int roomNum);
		void setPit(char pit);
		void setBat(char bat);
		void setMonster(char moster);
		void setAsVisited(char visited);
		void setPlayerSymbol(char symbol);
		void setRow(int row);
		void setColumn(int row);
		bool containsBat(char bat);
		///////////////////getters///////////////////////////
		int getRoomNum() const;
		char getPit() const;
		char getBat() const;
		char getMonster() const;
		char getVisited() const;
		char getPlayerSymbol() const;
		int getRow() const;
		int getColumn() const;
		///////////////////output operator overload//////////
		friend std::ostream & operator<<(std::ostream & output, const Room & rhs);
	private:
		char playerSymbol;
		int roomNum;
		char pit;
		char bat;
		char monster;
		char visited;
		int row;
		int column;
};

#endif // !ROOM_H