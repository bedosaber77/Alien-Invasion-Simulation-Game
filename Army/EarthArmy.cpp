#include "EarthArmy.h"
#include "../Units/Unit.h"

EarthArmy::EarthArmy()
{
}

void EarthArmy::AddUnit(Unit* newUnit)
{
	if (newUnit->getType() == earthSoliders)
		EarthSoliders.enqueue(newUnit);
	else if (newUnit->getType() == earthTank)
		EarthTanks.push(newUnit);
	else
	{
		//EG
	}
}

Unit* EarthArmy::removeUnit(UnitType type)
{
	Unit* unit=nullptr;
	switch (type)
	{
	case earthSoliders:EarthSoliders.dequeue(unit);
		break;
	case earthTank:EarthTanks.pop(unit);
		break;
	case earthGunnery://to be added 
		break;
	case alienSolider:
		break;
	case alienMonster:
		break;
	case alienDrone:
		break;
	default:
		break;
	}
	return unit;
}

void EarthArmy::Print()
{
}

EarthArmy::~EarthArmy()
{
}
