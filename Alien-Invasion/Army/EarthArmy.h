#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\Units\Earthsoldier.h"
#include "..\Units\Unit.h"
#include"../DS Files/Stack/ArrayStack.h"
#include "../DS Files/Priority Queue/priQueue.h"
#include "..\DEFS.h"


class EarthArmy
{
private:
	//Earth Army lists
	LinkedQueue <Unit*> EarthSoldiers;
	ArrayStack  <Unit*> EarthTanks;
	priQueue <Unit*> EarthGunneries;
	static int ID;
public:
	EarthArmy();

	//Adding and Removing unit from its list functions
	void AddUnit(Unit* newUnit);
	Unit* removeUnit(UnitType type);

	void Attack();
	void Print();
	void PrintFight(Unit* shooter);
	~EarthArmy();

};

