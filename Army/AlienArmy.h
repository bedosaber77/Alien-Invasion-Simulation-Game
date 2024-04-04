#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\DS Files\Queue\Deque.h"
#include "..\Units\Unit.h"

class AlienArmy
{
private:
	LinkedQueue <Unit*> AlienSoliders;
	Deque<Unit*>AlienDrones;
	Unit* Monsters[1000];
public:
	AlienArmy();
	void AddUnit(Unit* newUnit, int UnitNo);
	void DeleteUnit();
	void Print();
	~AlienArmy();

};

