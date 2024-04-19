#pragma once
#include<fstream>
#include<string>
#include"../DS Files/Queue/LinkedQueue.h"
#include "../RandGen Class/RandGen.h"
#include"../Army/AlienArmy.h"
#include"../Army/EarthArmy.h"
#include"../DEFS.h"

using namespace std;
class Game
{
	/*pointers to AlienArmy and EarthArmy classes
	to add and remove units from the list */
	AlienArmy* pAlienArmy;
	EarthArmy* pEarthArmy;

	//pointer to RandomGen class
	RandGen* pRand;

	//killed list
	LinkedQueue <Unit*> KilledList;

	int TimeStep = 1;

public:
	Game();
	void StartGame();

	bool LoadParameters(string);
	void MainLoop();	               // Increment time step until game ends
	void AddtoKilledList(Unit* army);  // Add killed units to the killed list
	void ClearKilledList();            // deallocate all units in the killed list


	//printing functions for the output file 
	void PrintKilledList() const;
	void Print() const;

	void TestCode();
	~Game();
};

