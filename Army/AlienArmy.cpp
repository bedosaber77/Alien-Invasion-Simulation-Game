#include "AlienArmy.h"
#include "..\DS Files\Queue\LinkedQueue.h"
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
	{	//AlienDrones.enqueue(newUnit);
	}
	else
	{
		Monsters[countMonsters] = newUnit;
		countMonsters++;
	}
}

Unit* AlienArmy::removeUnit(UnitType type)
{
	Unit* unit=nullptr;
	switch (type)
	{
	case earthSoliders:
		break;
	case earthTank:
		break;
	case earthGunnery:
		break;
	case alienSolider: AlienSoliders.dequeue(unit);
		break;
	case alienMonster: { 
		int randidx = rand() % countMonsters;
			unit = Monsters[randidx]; 
			Monsters[randidx] = Monsters[--countMonsters];
			Monsters[countMonsters] = nullptr;
		}
		break;
	case alienDrone:
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
