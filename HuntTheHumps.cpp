///////////////////////////////////////////////////////////////////////
// Names		     : Diego Guzman
// Date				 : 11/28/2017
// Project			 : Hunt the Wumpus 
// Course			 : CSS 342
// File Description  : This file represents the console application 
//					   entry point which contains the main() method and
//					   all the funtionalitites of the Hunt the Wumpus game.
///////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include "room.h"
#include "player.h"
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

///////////////////////////////////////////
///// Introduction to the Game ///////////
/////////////////////////////////////////
void introduction()
{
	cout << "                WELCOME TO HUNT THE WUMPUS" << endl;
	cout << "      GAME MODIFIED TO TEXT BY DG GAMING PRODUCTIONS" << endl;
	cout << endl;
	cout << " PRESS OPTION: " << endl;
	cout << "  i + enter = go north           | I + enter = shoots arrow north " << endl;
	cout << "  l + enter = go east            | L + enter = shoots arrow east  " << endl;
	cout << "  m + enter = go south           | M + enter = shoots arrow south " << endl;
	cout << "  j + enter = go west            | J + enter = shoots arrow west  " << endl;
	cout << "  e + enter = exit the game " << endl;
	cout << endl;
	cout << " MAP SYMBOLS: " << endl;
	cout << "	M = Monster " << endl;
	cout << "	B = Bat's   " << endl;
	cout << "	P = Pit's   " << endl;
	cout << "	V = Places visited " << endl;
	cout << "	MAP = Displays the map " << endl;
	cout << endl;
	cout << "The hunt is about to begin.... " << endl;
	cout << "But becareful... " << endl;
}
///////////////////////////////////////////
///// Maze constructor ///////////////////
/////////////////////////////////////////
void mazeContructor(Room(&roomArray)[8][8])
{	
	int counter = 0;
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j<8; j++)
		{
			Room room;
			room.setRoomNum(counter);
			roomArray[i][j] = room;
			counter++;
		}
	}

}
////////////////////////////////////////////////////
// Insert monster in randoms location in the maze//
//////////////////////////////////////////////////
Room monsterInsertion(Room(&roomArray)[8][8])
{
	int Mrow = rand() % 8;
	int Mcolumn = rand() % 8;
	roomArray[Mrow][Mcolumn].setMonster('M');
	roomArray[Mrow][Mcolumn].setRow(Mrow);
	roomArray[Mrow][Mcolumn].setColumn(Mcolumn);
	return roomArray[Mrow][Mcolumn];
}
///////////////////////////////////////////////////
// Insert bats in random locations in the maze////
/////////////////////////////////////////////////
void batInsertion(Room(&roomArray)[8][8]) 
{
	for (int p = 0; p<4; p++)
	{
		int Brow = rand() % 8;
		int Bcolumn = rand() % 8;
		roomArray[Brow][Bcolumn].setBat('B');
	}
}
///////////////////////////////////////////////////
// Insert pits in random locations in the maze////
/////////////////////////////////////////////////
void pitInsertion(Room(&roomArray)[8][8]) 
{
	for (int p = 0; p<4; p++)
	{
		int Prow = rand() % 8;
		int Pcolumn = rand() % 8;

		roomArray[Prow][Pcolumn].setPit('P');
	}
}
////////////////////////////////////////////////////////////////////
///// validStartingPositon() method determines ////////////////////
////if the player initial position is a valid position////////////
/////////////////////////////////////////////////////////////////
bool validStartingPosition(Player& mario, Room (&roomArray)[8][8]) 
{
	cout << endl;
	// mario starting coordinates
	cout << "You are in " << roomArray[mario.getCurrentR()][mario.getCurrentC()] << endl;

	if (roomArray[mario.getCurrentR()][mario.getCurrentC()].getVisited() == 'V')
	{
		cout << "You see footprint in the dust" << endl;
		cout << endl;
	}
	roomArray[mario.getCurrentR()][mario.getCurrentC()].setAsVisited('V');
	roomArray[mario.getCurrentR()][mario.getCurrentC()].setPlayerSymbol('C');
	// if mario appears in a location where there is a pit or a monster, mario dies 
	if (roomArray[mario.getCurrentR()][mario.getCurrentC()].getMonster() == 'M' || roomArray[mario.getCurrentR()][mario.getCurrentC()].getPit() == 'P')
	{
		//if mario appears where the moster is located, mario dies. 
		if (roomArray[mario.getCurrentR()][mario.getCurrentC()].getMonster() == 'M')
		{
			cout << "The Wumpus has eaten you! :( " << endl;
			cout << "Game Over" << endl;
			
			return false;
		}
		//if mario appears where a pit is located, mario dies.
		else
		{
			cout << "You have fallen into a pit! :( " << endl;
			cout << "Game Over!" << endl;
			return false;
		}

		//return false;
	}
	else if (roomArray[mario.getCurrentR()][mario.getCurrentC()].getBat() == 'B')
	{
		// remove the bat from current position
		roomArray[mario.getCurrentR()][mario.getCurrentC()].setBat('\0');

		// create new random numbers to insert the bat in a new location
		int batRow = rand() % 8;
		int batCol = rand() % 8;
		
		// if a bat is assign to a new room where another bat exists then
		// loop until it finds a new location where a bat doesn't exist
		while (roomArray[batRow][batCol].containsBat('B'))
		{
			roomArray[batRow][batCol].setBat('\0');

			int batRow = rand() % 8;
			int batCol = rand() % 8;
		}

		// insert the bat in a the location where there was no bat
		roomArray[batRow][batCol].setBat('B');

		// if you appear in a place where there is a bat you get transported to a new location
		int marioRow = rand() % 8;
		int marioCol = rand() % 8;

		//roomArray[marioRow][marioCol].setAsVisited('V');
		mario.setNewLocation(marioRow, marioCol);
		cout <<"You landed on a room with a bat, and he's flying you to a new room! :) " << endl;
		validStartingPosition(mario, roomArray);
	}
	else
		return true;
	
}
////////////////////////////////////////////////////////
/// Display the map with the monster, bats, and pits///
//////////////////////////////////////////////////////
void displayMaze(Room(&roomArray)[8][8])
{
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j<8; j++)
		{
			cout << "\t" << roomArray[i][j].getRoomNum()<<" "<<roomArray[i][j].getMonster()
				<<roomArray[i][j].getBat()<<roomArray[i][j].getPit()<<
				roomArray[i][j].getVisited();
		}
		cout << endl;
	}

}
/////////////////////////////////////////////////////////////////////////
/// moveMonster() method moves the monster everytime the arrow is shot /
///////////////////////////////////////////////////////////////////////
void moveMonster(Room(&roomArray)[8][8], Room monster)
{
	static Room monsterLocation = monster;	 
	bool isMoved = false;
	while (!isMoved)
	{
		int random = rand() % 5;

		if (random == 0)
		{  // this case the monster stays in its current position 
			return;
		}
		if (random == 1)
		{
			if (monsterLocation.getRow()>0) // sets the monster in the north room
			{
				roomArray[monsterLocation.getRow()][monsterLocation.getColumn()].setMonster('\0');
				int newcordinate = monsterLocation.getRow() - 1;
				roomArray[monsterLocation.getRow()-1][monsterLocation.getColumn()].setMonster('M');
				monsterLocation.setRow(newcordinate);
				isMoved = true;
			}
		}
		if (random == 2)
		{
			if (monsterLocation.getColumn()<=6) // sets the monster in the east room
			{
				roomArray[monsterLocation.getRow()][monsterLocation.getColumn()].setMonster('\0');
				int newcordinate = monsterLocation.getColumn() + 1;
				roomArray[monsterLocation.getRow()][monsterLocation.getColumn()+1].setMonster('M');
				monsterLocation.setColumn(newcordinate);
				isMoved = true;
			}

		}
		if (random == 3)
		{
			if (monsterLocation.getRow() <= 6) // sets the monster in the south room
			{
				roomArray[monsterLocation.getRow()][monsterLocation.getColumn()].setMonster('\0');
				int newcordinate = monsterLocation.getRow() + 1;
				roomArray[monsterLocation.getRow()+1][monsterLocation.getColumn()].setMonster('M');
				monsterLocation.setRow(newcordinate);
				isMoved = true;
			}
		}
		if (random == 4)
		{
			if (monsterLocation.getColumn() > 0) // sets the monster in the west room
			{
				roomArray[monsterLocation.getRow()][monsterLocation.getColumn()].setMonster('\0');
				int newcordinate = monsterLocation.getColumn() - 1;
				roomArray[monsterLocation.getRow()][monsterLocation.getColumn() - 1].setMonster('M');
				monsterLocation.setColumn(newcordinate);
				isMoved = true;
			}

		}

	}

}
/////////////////////////////////////////////////////////////////
/// checking for bats,monster, or pits from current location ///
///////////////////////////////////////////////////////////////
void checkAdjacentRooms(Player& mario, Room(&roomArray)[8][8]) 
{
	if (mario.getCurrentR() > 0)	// this if statement ensures there is room on top, and 
	{								// checks the the room on top for bats,monsters, or pits 	
		if (roomArray[mario.getCurrentR() - 1][mario.getCurrentC()].getBat() == 'B')
		{
			cout << "Warning: Hear Bats in the distance"<<endl;
		}
		if (roomArray[mario.getCurrentR() - 1][mario.getCurrentC()].getMonster() == 'M')
		{
			cout << "Warning: Smell something rank" << endl;
		}
		if (roomArray[mario.getCurrentR() - 1][mario.getCurrentC()].getPit() == 'P')
		{
			cout << "Warning: Feel a draft" << endl;
		}
	}
	if (mario.getCurrentR() <= 6)// this if statement ensures there is room on the bottom, and
	{							// checks the the room on top for bats,monsters, or pits 	
		if (roomArray[mario.getCurrentR() + 1][mario.getCurrentC()].getBat() == 'B')
		{
			cout << "Warning: Hear Bats in the distance" << endl;
		}
		if (roomArray[mario.getCurrentR() + 1][mario.getCurrentC()].getMonster() == 'M')
		{
			cout << "Warning: Smell something rank" << endl;
		}
		if (roomArray[mario.getCurrentR() + 1][mario.getCurrentC()].getPit() == 'P')
		{
			cout << "Warning: Feel a draft" << endl;
		}
	}
	if (mario.getCurrentC() > 0) // this if statement ensures there is a room on the left 
	{							// checks the the room on top for bats,monsters, or pits
		if (roomArray[mario.getCurrentR()][mario.getCurrentC()-1].getBat() == 'B')
		{
			cout << "Warning: Hear Bats in the distance" << endl;
		}
		if (roomArray[mario.getCurrentR()][mario.getCurrentC()-1].getMonster() == 'M')
		{
			cout << "Warning: Smell something rank" << endl;
		}
		if (roomArray[mario.getCurrentR()][mario.getCurrentC()-1].getPit() == 'P')
		{
			cout << "Warning: Feel a draft" << endl;
		}
	}
	if (mario.getCurrentC() <= 6)// this if statement ensures there is room to the right, and 
	{							// checks the the room on top for bats,monsters, or pits
		if (roomArray[mario.getCurrentR()][mario.getCurrentC() + 1].getBat() == 'B')
		{
			cout << "Warning: Hear Bats in the distance" << endl;
		}
		if (roomArray[mario.getCurrentR()][mario.getCurrentC() + 1].getMonster() == 'M')
		{
			cout << "Warning: Smell something rank" << endl;
		}
		if (roomArray[mario.getCurrentR()][mario.getCurrentC() + 1].getPit() == 'P')
		{
			cout << "Warning: Feel a draft" << endl;
		}
	}

}
//////////////////////////////////////////////////////
//// Moving the player up,east,south, and west //////
////////////////////////////////////////////////////
void playerMovements(Player& mario, Room(&roomArray)[8][8], Room monsterLocation)
{
	Player mNorth;
	Player mEast;
	Player mSouth;
	Player mWest;
	static int arrows = 4;
	string input;
	do
	{
		if (arrows == 0) 
		{
			cout << "No more arrows left" << endl;
			cout << "You Lose" << endl;
			return;
		}
		cout << "Arrows left: " << arrows << endl;
		checkAdjacentRooms(mario, roomArray);
		cout << "What is your next move: " << endl;
		cin >> input;
		cout << endl;
		if (input.compare("i")==0)  // The user inputs "i"
		{	// Move north
			mNorth = mario.goNorth();
			if (mNorth.getCurrentR() < 0 || mNorth.getCurrentR() > 7 || mNorth.getCurrentC() > 7 || mNorth.getCurrentC() < 0)
			{
				cout << "You hit a wall! " << endl;
				cout << endl;
				playerMovements(mario, roomArray,monsterLocation);
				return;
			}
			bool goingNorth = validStartingPosition(mNorth, roomArray);
			// if the player falls into a pit or in a monster, end the game
			if (goingNorth == false)
			{
				break;
			}
			// set marioNorth coordinates to mario
			mario.setCurrentR(mNorth.getCurrentR());
			mario.setCurrentC(mNorth.getCurrentC());
		}
		else if (input.compare("l")==0)// The user inputs "l"
		{   // Move east
			mEast = mario.goEast();
			if (mEast.getCurrentR() < 0 || mEast.getCurrentR() > 7 || mEast.getCurrentC() > 7 || mEast.getCurrentC() < 0)
			{
				cout << "You hit a wall! " << endl;
				cout << endl;
				playerMovements(mario, roomArray, monsterLocation);
				return;
			}
			bool goingEast = validStartingPosition(mEast, roomArray);
			// if the player falls into a pit or in a monster house, end the game
			if (goingEast == false)
			{
				break;
			}
			mario.setCurrentR(mEast.getCurrentR());
			mario.setCurrentC(mEast.getCurrentC());
		}
		else if (input.compare("m")==0) // The user inputs "m"
		{   // Move south
			mSouth = mario.goSouth();

			if (mSouth.getCurrentR() < 0 || mSouth.getCurrentR() > 7 || mSouth.getCurrentC() < 0 || mSouth.getCurrentC() > 7)
			{
				cout << "You hit the a wall!" << endl;
				cout << endl;
				playerMovements(mario, roomArray, monsterLocation);
				return;
			}
			bool goingSouth = validStartingPosition(mSouth, roomArray);
			// if the player falls into a pit or in a monster house, end the game
			if (goingSouth == false)
			{
				break;
			}
			mario.setCurrentR(mSouth.getCurrentR());
			mario.setCurrentC(mSouth.getCurrentC());
			//displayMaze(roomArray);
		}
		else if (input.compare("j")==0) // The user inputs "j" 
		{   // Move west
			mWest = mario.goWest();
			if (mWest.getCurrentR() < 0 || mWest.getCurrentR() > 7 || mWest.getCurrentC() < 0 || mWest.getCurrentC() > 7)
			{
				cout << "You hit a wall!" << endl;
				cout << endl;
				playerMovements(mario, roomArray, monsterLocation);
				return;
			}
			bool goingWest = validStartingPosition(mWest, roomArray);
			// if the player falls into a pit or in a monster house, end the game
			if (goingWest == false)
			{
				break;
			}
			mario.setCurrentR(mWest.getCurrentR());
			mario.setCurrentC(mWest.getCurrentC());
		}
		else if (input.compare("I")==0) //The user shoots arrow north by pressing "I"
		{
			if (mario.getCurrentR() > 0) // makes sures there is a room on top
			{	
				if (roomArray[mario.getCurrentR() - 1][mario.getCurrentC()].getMonster() == 'M') 
				{
					cout << "You have killed the Wumpus! :) " << endl;
					return;
				}
			}
			arrows= arrows - 1;
			moveMonster(roomArray, monsterLocation);
			cout << "You missed! " << endl;
		}
		else if (input.compare("L")==0) //The user shoots arrow east by pressing "L" 
		{
			if (mario.getCurrentC()<=6) //It makes sures there is a room to the right
			{
				if (roomArray[mario.getCurrentR()][mario.getCurrentC()+1].getMonster() == 'M') 
				{
					cout << "You have killed the Wumpus! :) " << endl;
					return;
				}
			}
			arrows = arrows - 1;
			moveMonster(roomArray, monsterLocation);
			cout << "You missed! " << endl;
		}
		else if (input.compare("M")==0) //The user shoots arrow north by pressing "M"
		{
			if (mario.getCurrentR() <= 6) // it makes sure there is a room at the bottom 
			{
				if (roomArray[mario.getCurrentR()+1][mario.getCurrentC()].getMonster()=='M') 
				{
					cout << "You have killed the Wumpus! :) " << endl;
					return;
				}
			}
			arrows = arrows - 1;
			moveMonster(roomArray, monsterLocation);
			cout << "You missed! " << endl;
		}
		else if (input.compare("J")==0) //The user shoots arrow west by pressing "J"
		{
			if (mario.getCurrentC() > 0) //it makes sure there is a room to the left 
			{
				if (roomArray[mario.getCurrentR()][mario.getCurrentC()-1].getMonster()=='M') 
				{
					cout << "You have killed the Wumpus! :) " << endl;
					return;
				}
			}
			arrows = arrows - 1;
			moveMonster(roomArray, monsterLocation);
			cout << "You missed! " << endl;
		}
		else if (input.compare("MAP")==0 || input.compare("map") == 0)
		{
			displayMaze(roomArray);
		}

	} while (input.compare("e")!= 0);
	return;
}
///////////////////////////////////////////////////////////
//////////Main Method/////////////////////////////////////
/////////////////////////////////////////////////////////
int main()
{
	srand(time(0));
	introduction(); // displays the introduction 

	Room roomArray[8][8]; // Initializing a multidimentional array of rooms 

	mazeContructor(roomArray); // creating an 8 by 8 maze 

	Room monsterLocation = monsterInsertion(roomArray); // inserting a monster in the maze

	batInsertion(roomArray); // inserting a bats in the maze
	
	pitInsertion(roomArray);  // inserting a pits in the maze
 
	// select random initial position for the player
	int marioRow = rand() % 8;
	int marioCol = rand() % 8;

	// set the player to the starting position
	Player mario(marioRow, marioCol);

	// if the starting position is a monster or a pit return false and end the game
	bool startingPosition = validStartingPosition(mario, roomArray);
	
	// end the game
	if (startingPosition == false) 
	{
		system("pause");
		return 0;
	}
	playerMovements(mario, roomArray, monsterLocation);
	system("pause");
    return 0;
}

