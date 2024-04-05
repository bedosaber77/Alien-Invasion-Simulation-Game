#pragma once
#include<fstream>
#include<string>
#include"../DS Files/Queue/LinkedQueue.h"
#include"RandGen.h"
#include"../Army/AlienArmy.h"
#include"../Army/EarthArmy.h"
#include"RandGen.h"
#include"Parameters.h"

using namespace std;
class Game
{
	/*pointers to AlienArmy and EarthArmy classes
	to add and remove units from the list */
	AlienArmy* pAlienArmy;
	EarthArmy* pEarthArmy;

	//pointer to RandomGen class
	RandGen* pRand;

	int TimeStep=1;

	//bool isOver; // boolean for ending the game

	//killed and temp lists
	LinkedQueue <Unit*> KilledList;
	LinkedQueue <Unit*> TempList;


public:
	Game();
	void StartGame();
	void LoadParameters(string);
	void MainLoop();	// Increment time step until game ends
	void AddtoKilledList(Unit* army);
	void AddtoTempList(Unit* army);
	void ClearKilledList();       // deallocate all units in the killed list

	/*
	* Maybe phase 2 functions
	bool CheckWin();    // check win to end the game
	bool CheckGameOver(); // to be revisited
	*/

	void Print();                // output file 
	~Game();
};

