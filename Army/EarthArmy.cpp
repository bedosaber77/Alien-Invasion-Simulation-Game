#include "EarthArmy.h"

EarthArmy::EarthArmy()
{
}

void EarthArmy::AddUnit(Unit* newUnit,int UnitNo)
{
	if (UnitNo == 1)
		EarthSoliders.enqueue(newUnit);
	else if (UnitNo == 2)
		EarthTanks.push(newUnit);
	else
	{
		//EG
	}
}

void EarthArmy::DeleteUnit()
{
}

void EarthArmy::Print()
{
}

EarthArmy::~EarthArmy()
{
}
