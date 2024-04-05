#include "EarthArmy.h"
#include "../Units/Unit.h"
#include "../Units/EarthGunnery.h"

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
		EarthGunnery* earthgunnery = dynamic_cast<EarthGunnery*>(newUnit);
		int priorty = earthgunnery->getCombination();
		EarthGunnerys.enqueue(newUnit, priorty);
	}
}

Unit* EarthArmy::removeUnit(UnitType type)
{
	Unit* unit=nullptr;
	int priorty;
	switch (type)
	{
	case earthSoliders:EarthSoliders.dequeue(unit);
		break;
	case earthTank:EarthTanks.pop(unit);
		break;
	case earthGunnery:EarthGunnerys.dequeue(unit, priorty);
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
