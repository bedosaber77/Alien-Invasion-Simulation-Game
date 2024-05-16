#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\Units\Unit.h"

class AllyArmy
{
private:

	//Ally Army list
	LinkedQueue<Unit*> SaverUnits;
	static int ID;

public:
	AllyArmy();

	//Adding and Removing unit from its list functions
	void AddUnit(Unit* newUnit);
	Unit* removeUnit();
	

	// Count Alive Units for the output file
	int GetSUcount() const;
	int GetID() const;


	//Fighting Functions
	void Attack();
	void Print() const;

	~AllyArmy();

};

