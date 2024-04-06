#include "AlienArmy.h"
#include "..\Units\AlienSolider.h"
#include "..\Units\Unit.h"
#include <time.h>
#include <cstdlib>

AlienArmy::AlienArmy()
{
	srand(time(0));
	countMonsters = 0;
}

void AlienArmy::AddUnit(Unit* newUnit)
{
	if (newUnit->getType() == alienSolider)
		AlienSoliders.enqueue(newUnit);
	else if (newUnit->getType() == alienDrone)
		AlienDrones.enqueue(newUnit);
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
		if (AlienSoliders.getCount() == 0)
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
		if (AlienDrones.getCount() == 0)
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
}

AlienArmy::~AlienArmy()
{
}
