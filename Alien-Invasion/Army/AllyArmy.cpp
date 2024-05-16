#include "AllyArmy.h"
#include <iostream>
using namespace std;


AllyArmy::AllyArmy ()
{
}

//==================================================================================//
//								Add / Remove Functions	     						//
//==================================================================================//

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

/*
 To remove a unit from its list
  1- If the List is empty return nullptr
  2- else remove a unit and return it
*/
Unit* AllyArmy::removeUnit()
{
	Unit* unit=nullptr;
	SaverUnits.dequeue(unit);
	return unit;
}


//==================================================================================//
//							     Getters Functions	          						//
//==================================================================================//
int AllyArmy::GetSUcount() const
{
	return SaverUnits.getCount();
}

int AllyArmy::GetID() const
{
	return ID;
}

//==================================================================================//
//							      	Fighting Functions       						//
//==================================================================================//

void AllyArmy::Attack()
{
	Unit* unit=nullptr;
	if (SaverUnits.peek(unit))
		unit->Attack();
}

void AllyArmy::Print() const
{
	cout << SaverUnits.getCount() << " SU [";
	SaverUnits.print();
	cout << "]\n";
}

AllyArmy::~AllyArmy()
{
	Unit* DeletedUnit = nullptr;
	while (!SaverUnits.isEmpty())
	{
		SaverUnits.dequeue(DeletedUnit);
		delete DeletedUnit;
		DeletedUnit = nullptr;
	}
}



int AllyArmy::ID = 4000;
