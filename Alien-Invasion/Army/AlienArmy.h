#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\DS Files\Queue\Deque.h"
#include "..\DS Files\ArrayADT.h"
#include "..\Units\Unit.h"
#include "..\DEFS.h"

class AlienArmy
{
private:

	//Alien Army lists
	LinkedQueue <Unit*> AlienSoldiers;
	Deque <Unit*> AlienDrones;
	ArrayADT <Unit*> AlienMonsters;

	static int ID;
public:
	AlienArmy();

	//Adding and Removing unit from its list functions
	void AddUnit(Unit* newUnit,bool IntoFront=false);
	Unit* removeUnit(UnitType type,bool FromBack=false);

	

	// Count Alive Units for the output file
	int GetAScount();
	int GetAMcount();
	int GetADcount();

	int GetID();


	//Fighting Functions
	void Attack();
	void Print();

	~AlienArmy();

};

