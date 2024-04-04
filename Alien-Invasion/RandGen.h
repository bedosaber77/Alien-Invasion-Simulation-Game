#pragma once
#include"Parameters.h"
#include"../Army/AlienArmy.h"
#include"../Army/EarthArmy.h"
class RandGen
{
	EarthArmy* pEarthArmy;
	AlienArmy* pAlienArmy;
public:
	RandGen();
	void GenerateUnits(int N,int Prob,Inputs EarthParameters, Inputs AlienParameters,int ts);
	~RandGen();

};

