#include "AlienArmy.h"
#include "..\Units\Aliensoldier.h"
#include "..\Units\Unit.h"
#include <time.h>
#include <cstdlib>

AlienArmy::AlienArmy()
{
	srand(time(0));
}

void AlienArmy::AddUnit(Unit* newUnit,bool IntoFront)
{
	//Check if the unit is a new unit or it has returned from the war to set its ID correctly
	if (newUnit->getID() == 0)
	{
		newUnit->setID(ID);
		ID++;
	}

	//Add each unit to its list according to its type
	if (newUnit->getType() == alienSoldier)
		AlienSoldiers.enqueue(newUnit);
	else if (newUnit->getType() == alienDrone)
	{
		if(IntoFront)
			AlienDrones.enqueueFront(newUnit);
		else
		AlienDrones.enqueue(newUnit);
	}
	else
	{
		AlienMonsters.insert(newUnit);
	}
}

/*
 To remove a unit from its list
  1- If the List is empty return nullptr
  2- else remove a unit and return it
*/
Unit* AlienArmy::removeUnit(UnitType type,bool fromBack)
{
	Unit* unit=nullptr;
	switch (type)
	{
	case alienSoldier:
	{ 
		if (AlienSoldiers.isEmpty())
			return nullptr;
		AlienSoldiers.dequeue(unit);
	}
		break;
	case alienMonster: 
	{ 
		if (AlienMonsters.isEmpty())
			return nullptr;
	
		int randidx = rand() % AlienMonsters.getCount();
		AlienMonsters.remove(unit, randidx);
	}
		break;
	case alienDrone: 
	{
		if (AlienDrones.isEmpty())
			return nullptr;
		if (fromBack)
			AlienDrones.dequeueBack(unit);
		else
			AlienDrones.dequeue(unit);
	}
		break;
	default:
		break;
	}
	return unit;
}

bool AlienArmy::Attack()
{
	Unit* unit2 = nullptr;
	bool SuccusfulAttack = false;
	//AS Attack

	if (AlienSoldiers.peek(unit2))
	{
		SuccusfulAttack = unit2->Attack();
	}


	//AM Attack
	if (AlienMonsters.getCount()) 
	{
		int randidx = rand() % AlienMonsters.getCount();
		if (AlienMonsters.getItem(unit2, randidx))
		{
			SuccusfulAttack = unit2->Attack() || SuccusfulAttack;
		}
	}


	//AD Attack in pairs


	if (AlienDrones.getCount() > 1)
	{
		AlienDrones.peek(unit2);
		if (unit2)
		{
			SuccusfulAttack = unit2->Attack() || SuccusfulAttack;
		}

		AlienDrones.peekBack(unit2);
		if (unit2)
		{
			SuccusfulAttack = unit2->Attack() || SuccusfulAttack;
		}

	}
	return SuccusfulAttack;
}

int AlienArmy::GetAScount()
{
	return AlienSoldiers.getCount();
}

int AlienArmy::GetAMcount()
{
	return AlienMonsters.getCount();
}

int AlienArmy::GetADcount()
{
	return AlienDrones.getCount();
}

void AlienArmy::Print()
{
	cout << AlienSoldiers.getCount() << " AS [";
	AlienSoldiers.print();
	cout << "]\n";
	cout << AlienMonsters.getCount() << " AM [";
	AlienMonsters.print();
	cout << "]\n";
	cout << AlienDrones.getCount() << " AD [";
	AlienDrones.print();
	cout << "]";
}

AlienArmy::~AlienArmy()
{
	Unit* DeletedUnit;
	while (!AlienSoldiers.isEmpty())
	{
		AlienSoldiers.dequeue(DeletedUnit);
		delete DeletedUnit;
		DeletedUnit = nullptr;
	}

	while (!AlienDrones.isEmpty())
	{
		AlienDrones.dequeue(DeletedUnit);
		delete DeletedUnit;
		DeletedUnit = nullptr;
	}

	while (!AlienMonsters.isEmpty())
	{
		int index = 0;
		AlienMonsters.remove(DeletedUnit, index++);
		delete DeletedUnit;
		DeletedUnit = nullptr;
	}

	
}

int AlienArmy::ID = 2000;