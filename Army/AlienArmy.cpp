#include "AlienArmy.h"
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\Units\AlienSolider.h"
#include "..\Units\Unit.h"

AlienArmy::AlienArmy()
{
}

void AlienArmy::AddUnit(Unit* newUnit, int UnitNo)
{
	if (UnitNo == 1)
		AlienSoliders.enqueue(newUnit);
	else if (UnitNo == 2)
		AlienDrones.enqueue(newUnit);
	else
	{
		// Monsters Count to be revisited
	}
}



void AlienArmy::DeleteUnit()
{
}

void AlienArmy::Print()
{
}

AlienArmy::~AlienArmy()
{
}
