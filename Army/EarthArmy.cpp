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
	case earthSoliders: {
		if (EarthSoliders.getCount() == 0)
			return nullptr;
		EarthSoliders.dequeue(unit);
	}
		break;
	case earthTank: { 
		if (EarthTanks.getCount() == 0)
			return nullptr;
		EarthTanks.pop(unit); 
		}
		break;
	case earthGunnery: { 
		if (EarthGunnerys.getCount() == 0)
			return nullptr;
		EarthGunnerys.dequeue(unit, priorty);
		}
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
