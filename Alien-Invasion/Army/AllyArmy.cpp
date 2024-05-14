#include "AllyArmy.h"
#include <iostream>
using namespace std;


AllyArmy::AllyArmy ()
{
}

void AllyArmy::AddUnit(Unit* newUnit)
{
	if (newUnit&&newUnit->getID() == 0)
	{
		newUnit->setID(ID);
		ID++;
	}
	if(newUnit)
		SaverUnits.enqueue(newUnit);
}

Unit* AllyArmy::removeUnit()
{
	Unit* unit=nullptr;
	SaverUnits.dequeue(unit);
	return unit;
}

int AllyArmy::GetSUcount() const
{
	return SaverUnits.getCount();
}

int AllyArmy::GetID() const
{
	return ID;
}

void AllyArmy::Attack()
{
	Unit* unit;
	if (SaverUnits.peek(unit))
		unit->Attack();
}

void AllyArmy::Print() const
{
	cout << SaverUnits.getCount() << " SU [";
	SaverUnits.print();
	cout << "]\n";
}

void AllyArmy::SuWithdraw()
{
	Unit* unit;
	while (SaverUnits.dequeue(unit));
}



int AllyArmy::ID = 4000;
