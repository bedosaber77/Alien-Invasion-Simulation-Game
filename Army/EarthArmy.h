#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\Units\EarthSolider.h"
#include "..\Units\Unit.h"
#include"../DS Files/Stack/ArrayStack.h"
#include "../DS Files/Priority Queue/priQueue.h"

class EarthArmy
{
private:
	LinkedQueue <Unit*> EarthSoliders;
	ArrayStack  <Unit*> EarthTanks;
	priQueue <Unit*> EarthGunnerys;
public:
	EarthArmy();
	void AddUnit(Unit* newUnit);
	Unit* removeUnit(UnitType type);
	void Attack();
	void Print();
	~EarthArmy();

};

