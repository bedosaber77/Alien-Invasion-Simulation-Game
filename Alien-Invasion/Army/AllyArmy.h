#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\Units\Unit.h"

class AllyArmy
{
private:
	LinkedQueue<Unit*> SaverUnits;
	static int ID;

public:
	AllyArmy();

	void AddUnit(Unit* newUnit);
	Unit* removeUnit();
	
	int GetSUcount() const;
	int GetID() const;

	void Attack();
	void Print() const;
	void SuWithdraw();

};

