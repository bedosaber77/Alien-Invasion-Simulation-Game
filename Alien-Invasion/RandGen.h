#pragma once
#include"Parameters.h"
#include"../Army/AlienArmy.h"
#include"../Army/EarthArmy.h"
#include <cstdlib>
#include <time.h>
#include<string>
using namespace std;
enum ArmyType
{ Earth,Alien};
class RandGen
{
	
	int N, Prob;
	Inputs EarthParameters,AlienParameters;
	ArmyType Army_Type;
	
public:
	RandGen();

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


	~RandGen();

};

