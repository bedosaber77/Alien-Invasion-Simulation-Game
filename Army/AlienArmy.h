#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\DS Files\Queue\Deque.h"
#include "..\Units\Unit.h"
#include "..\Alien-Invasion\DEFS.h"

class AlienArmy
{
private:
	LinkedQueue <Unit*> AlienSoldiers;
	Deque <Unit*> AlienDrones;
	Unit* AlienMonsters[1000];
	int countMonsters;
	static int ID;
public:
	AlienArmy();

	//Adding and Removing unit from its list functions
	void AddUnit(Unit* newUnit,bool IntoFront=false);
	Unit* removeUnit(UnitType type,bool FromBack=false);

	void Attack();

	//Getters for Lists needed by Attack function
	

	void Print();
	~AlienArmy();

};

