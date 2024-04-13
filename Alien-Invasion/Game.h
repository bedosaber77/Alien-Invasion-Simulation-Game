#pragma once
#include<fstream>
#include<string>
#include"../DS Files/Queue/LinkedQueue.h"
#include"RandGen.h"
#include"../Army/AlienArmy.h"
#include"../Army/EarthArmy.h"
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

	// We need to get RandGen and Armies Pointers    (As mentioned in Q&A File)


	AlienArmy* GetAlienArmyPtr();
	EarthArmy* GetEarthArmyPtr();
	RandGen* GetRandGenPtr();

	void GetEnemiesList(ArmyType Army_Type,UnitType Unit_Type, int Capacity, LinkedQueue<Unit*>& EnemiesList);	//to be revisited

	// Get Current Time              (To be discussed ,what do you think about consistency?)


	int GetCurrentTime();

	/*
	* Maybe phase 2 functions
	bool CheckWin();    // check win to end the game
	bool CheckGameOver(); // to be revisited
	*/

	void PrintKilledList();
	void Print();                // output file 
	~Game();
};

