#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\Units\EarthSolider.h"
#include "..\Units\Unit.h"
#include"../DS Files/Stack/ArrayStack.h"


class EarthArmy
{
private:
	LinkedQueue <Unit*> EarthSoliders;
	ArrayStack<Unit*>EarthTanks;
public:
	EarthArmy();
	void AddUnit(Unit* newUnit, int UnitNo);
	void DeleteUnit();
	void Print();
	~EarthArmy();

};

