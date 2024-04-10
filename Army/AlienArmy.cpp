#include "AlienArmy.h"
#include "..\Units\AlienSolider.h"
#include "..\Units\Unit.h"
#include <time.h>
#include <cstdlib>

AlienArmy::AlienArmy()
{
	srand(time(0));
	countMonsters = 0;
	//for (int i = 0; i < 1000; i++)
		//Monsters[i] = nullptr;

}

void AlienArmy::AddUnit(Unit* newUnit,bool IntoFront)
{
	if (newUnit->getID() == 0)
	{
		newUnit->setID(ID);
		ID++;
	}
	if (newUnit->getType() == alienSolider)
		AlienSoliders.enqueue(newUnit);
	else if (newUnit->getType() == alienDrone)
	{
		if(IntoFront)
			AlienDrones.enqueueFront(newUnit);
		else
		AlienDrones.enqueue(newUnit);
	}
	else
	{
		Monsters[countMonsters] = newUnit;
		countMonsters++;
	}
}

Unit* AlienArmy::removeUnit(UnitType type,bool fromBack)
{
	Unit* unit=nullptr;
	switch (type)
	{
	case alienSolider: { 
		if (AlienSoliders.isEmpty())
			return nullptr;
		AlienSoliders.dequeue(unit);
		}
		break;
	case alienMonster: { 
		if (countMonsters == 0)
			return nullptr;
		int randidx = rand() % countMonsters;
			unit = Monsters[randidx]; 
			Monsters[randidx] = Monsters[--countMonsters];
			Monsters[countMonsters] = nullptr;
		}
		break;
	case alienDrone: {
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



void AlienArmy::Print()
{
	cout << AlienSoliders.getCount() << " AS [";
	AlienSoliders.print();
	cout << "]\n";
	cout << countMonsters << " AM [";
	for (int i = 0; i < countMonsters; i++)
	{
		cout<< Monsters[i]->getID();
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
}

int AlienArmy::ID = 2000;