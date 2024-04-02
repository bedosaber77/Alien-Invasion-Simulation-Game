#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\Units\EarthSolider.h"
#include "..\Units\Unit.h"

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

