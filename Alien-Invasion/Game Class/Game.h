#pragma once
#include<fstream>
#include<string>
#include"../DS Files/Queue/LinkedQueue.h"
#include "../RandGen Class/RandGen.h"
#include"../Army/AlienArmy.h"
#include"../Army/EarthArmy.h"
#include"../DEFS.h"
#include "../Army/AllyArmy.h"

using namespace std;
class Game
{
	/*pointers to AlienArmy and EarthArmy classes
	to add and remove units from the list */
	AlienArmy* pAlienArmy;
	EarthArmy* pEarthArmy;
	AllyArmy* pAllyArmy;
	//pointer to RandomGen class
	RandGen* pRand;

	//killed list
	LinkedQueue <Unit*> KilledList;
	
	//UML
	priQueue <Unit*> UMLsolider;
	LinkedQueue <Unit*> UMLtanks;

	int TimeStep = 1;

	//Killed Units Counters
	int ESDead, EGDead, ETDead, HUDead, ASDead, ADDead, AMDead; 

	// Duration Parameters
	int Dfearth, Ddearth, Dbearth;    //Df, Dd, Db for earth army counters
	int Dfalien, Ddalien, Dbalien;    //Df, Dd, Db for alien army counters

	int HealedUnits;  //No of units healed successfully

	// EndGame Parameters
	bool SilentMode;   //checks the mode of the game (S/I)
	bool EndGame;     //checks the end of the game  
	string FinalResult;  //stores the final result (win/tie/loss)

	int InfectionProb;  //the probability an alien monster infects earth soldiers
	int TotalInfectedUnits;  //No of units infected from the start of the game
	int CurrentInfectedUnits;  //No of units currently infected
	int UMLInfectedUnits;   //No of currently infected units is uml
	int ImmunedUnits;   //No of immuned units

	int InfectionThreshold;  //infection threshold loaded from the input file

	//Saver Units Required Parameters
	bool CallAlly;   //when set to true earth army calls for help from the allied army
	bool AllyWithdraw;  //when set to true allied army is destroyed and not generated anymore
	
public:
	Game();

	//Functions needed at the beginning of the game
	void StartGame();
	bool LoadParameters(string);

	void GenerateArmy(bool Ally=false);  //generates number of units each time step

	void MainLoop();   // Increment time step until game ends
	void AddtoKilledList(Unit* army);  // Add killed units to the killed list

	//Output File Needed functions
	void SetOutFile();  //Start the output file
	void AddtoOutFile(Unit* killedUnit);  //Add info of each killed unit to the output file
	void GameStatistics() const;  //Calculate game statistics at the end of the game
	void CheckResult();  //check result each time step after 40
	int GetCount(UnitType Unit_Type) const;  //return total count of each unit from the beginning of the game


	//Heal functions
	void AddtoUML(Unit* unit);  //Add earth units to UML
	bool UMLisEmpty() const;  //check if the UML is empty or not
	Unit* getUnitToHeal();  //returns damaged unit for the heal unit to heal
	void UpdateHealCount();  //increment healed units when healed successfully
	void DestroyUML();

	//Infection functions
	int getInfectionProb() const;
	void IncrementInfectedCount();
	void DecrementInfectedCount();
	void CheckAllyWithdraw();
	bool GetCallAlly() const;

	//Needed functions for attack
	Unit* GetEnemiesUnit(ArmyType Army_Type, UnitType Unit_Type, bool BackDrone = 0) const;  //return enemy for the unit to attack 

	//RandGen and Armies Pointers Getters
	AlienArmy* GetAlienArmyPtr() const;
	EarthArmy* GetEarthArmyPtr() const;
	AllyArmy* GetAllyArmyPtr() const;
	RandGen* GetRandGenPtr() const;

	// Current Time Getter       
	int GetCurrentTime() const;

	//printing functions 
	void PrintKilledList() const;
	void PrintFight(Unit* shooter, LinkedQueue<Unit*> fightingUnits, bool InfectionList = false) const;
	void PrintAliveUnits() const;
	void PrintUMLList() const;
	void SpreadInfectedUnits();


	~Game();
};

