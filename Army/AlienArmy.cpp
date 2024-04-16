#include "AlienArmy.h"
#include "..\Units\AlienSolider.h"
#include "..\Units\Unit.h"
#include <time.h>
#include <cstdlib>

AlienArmy::AlienArmy()
{
	srand(time(0));
	countMonsters = 0;
	for (int i = 0; i < 1000; i++)
	    AlienMonsters[i] = nullptr;
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
		AlienMonsters[countMonsters] = newUnit;
		countMonsters++;
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
		if (countMonsters == 0)
			return nullptr;
		int randidx = rand() % countMonsters;
			unit = AlienMonsters[randidx]; 
			AlienMonsters[randidx] = AlienMonsters[--countMonsters];
			AlienMonsters[countMonsters] = nullptr;
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

void AlienArmy::Attack()
{
	Unit* unit2 = nullptr;

	//AS Attack

	if (AlienSoldiers.peek(unit2))
	{
		unit2->Attack();
	}


	//AM Attack





	//AD Attack in pairs
	if (AlienDrones.getCount() > 1)
	{
		AlienDrones.peek(unit2);
		if (unit2)
		{
			unit2->Attack();
		}

		AlienDrones.peekBack(unit2);
		if (unit2)
		{
			unit2->Attack();
		}

	}
}


///Getters For Lists







void AlienArmy::Print()
{
	cout << AlienSoldiers.getCount() << " AS [";
	AlienSoldiers.print();
	cout << "]\n";
	cout << countMonsters << " AM [";
	for (int i = 0; i < countMonsters; i++)
	{
		cout<< AlienMonsters[i]->getID();
		if (i + 1 < countMonsters)
			cout << ", ";
	}
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

	for (int i = 0; i < countMonsters; i++)
	{
		delete AlienMonsters[i];
		AlienMonsters[i] = nullptr;
	}
}

int AlienArmy::ID = 2000;