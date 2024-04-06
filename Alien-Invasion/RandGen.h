#pragma once
#include"Parameters.h"
#include"../Army/AlienArmy.h"
#include"../Army/EarthArmy.h"
#include <cstdlib>
#include <time.h>

class RandGen
{
	EarthArmy* pEarthArmy;
	AlienArmy* pAlienArmy;
	int N, Prob;
	Inputs EarthParameters,AlienParameters;
public:
	RandGen();

	//setters for Input File
	void SetN(int);
	void SetProb(int);
	void SetEarthParameters(Inputs);
	void SetAlienParameters(Inputs);


	// Unit Generation Function
	void GenerateUnits(int N, int Prob, Inputs EarthParameters, Inputs AlienParameters, int ts);


	~RandGen();

};

