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

	//HL
	ArrayStack <Unit*> HL;
	int HealedUnits;


public:
	EarthArmy();

	//Adding and Removing unit from its list functions
	void AddUnit(Unit* newUnit);
	Unit* removeUnit(UnitType type);

	// Count Alive Units for the output file
	int GetEScount() const;
	int GetEGcount() const;
	int GetETcount() const;
	int GetHUcount() const;

	int GetID() const;

	//Fighting Functions
	void Attack();
	void Print() const;
	bool SpreadInfection(Unit* &infectedUnit);

	~EarthArmy();

};

