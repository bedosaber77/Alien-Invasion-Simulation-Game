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
	
	//UML
	priQueue <Unit*> UMLsolider;
	LinkedQueue <Unit*> UMLtanks;

	int TimeStep = 1;

	//units counters
	//int EScount, EGcount, ETcount, AScount, ADcount, AMcount
	int ESDead, EGDead, ETDead, ASDead, ADDead, AMDead;
	int Dfearth, Ddearth, Dbearth;
	int Dfalien, Ddalien, Dbalien;

	int HealedUnits;
	bool SilentMood;
	bool EndGame;

	string FinalResult; 


public:
	Game();
	void StartGame();

	bool LoadParameters(string);

	//Output File Needed functions
	void SetOutFile();
	void AddtoOutFile(Unit* killedUnit);
	void GameStatistics();
	void CheckResult();
	int GetCount(UnitType Unit_Type);
	void UpdateHealCount();

	void MainLoop();	               // Increment time step until game ends
	void AddtoKilledList(Unit* army);  // Add killed units to the killed list
	void ClearKilledList();            // deallocate all units in the killed list

	void AddtoUML(Unit* unit);
	bool UMLisEmpty();
	Unit* getUnitToHeal();

	// We need to get RandGen and Armies Pointers    (As mentioned in Q&A File)
	AlienArmy* GetAlienArmyPtr();
	EarthArmy* GetEarthArmyPtr();
	RandGen* GetRandGenPtr();

	Unit* GetEnemiesUnit(ArmyType Army_Type,UnitType Unit_Type,bool BackDrone=0);	//to be revisited

	// Get Current Time              (To be discussed ,what do you think about consistency?)
	int GetCurrentTime();

	

	/*
	* Maybe phase 2 functions
	bool CheckWin();    // check win to end the game
	bool CheckGameOver(); // to be revisited
	*/

	//printing functions for the output file 
	void PrintKilledList() const;
	void PrintFight(Unit* shooter, UnitType shooterType, LinkedQueue<int> fightingUnits);
	void PrintAliveUnits() const;
	void PrintUMLList() const;


	~Game();
};

