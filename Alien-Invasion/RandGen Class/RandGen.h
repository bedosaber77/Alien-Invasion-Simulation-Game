#pragma once
#include"../Army/AlienArmy.h"
#include"../Army/EarthArmy.h"
#include <cstdlib>
#include <time.h>
#include<string>
//#include "..\Alien-Invasion\DEFS.h"
#include"../DEFS.h"
using namespace std;
class Game;
class RandGen
{
	int N, Prob;
	Inputs EarthParameters,AlienParameters;
	ArmyType Army_Type;
	Game* pGame;

	//Units Counters
	int EScount;
	int EGcount;
	int ETcount;
	int AScount;
	int ADcount;
	int AMcount;

public:
	RandGen(Game*);

	//setters for Input File
	void SetN(int);
	void SetProb(int);
	void SetEarthParameters(Inputs);
	void SetAlienParameters(Inputs);


	//getters for Input file
	int GetN() const;
	int GetProb() const;

	// Unit Generation Function
	Unit* GenerateUnits( int ts, ArmyType Army_Type);


	//returns all count numbers by reference
	void GetUnitsNo(int& ES, int& EG, int& ET, int& AS, int& AD, int& AM);

	~RandGen();

};

