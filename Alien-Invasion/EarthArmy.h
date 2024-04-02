#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\Alien-Invasion\EarthSolider.h"
#include "..\Alien-Invasion\Unit.h"

class EarthArmy
{
private:
	LinkedQueue <Unit*> EarthSoliders;
public:
	EarthArmy();
	void AddEarthSolider(Unit* AlienUnit);
	void DeleteUnit();
	void Print();
	~EarthArmy();

};

