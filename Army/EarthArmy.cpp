#include "EarthArmy.h"
#include "../Units/Unit.h"
#include "../Units/EarthGunnery.h"

EarthArmy::EarthArmy()
{
}

void EarthArmy::AddUnit(Unit* newUnit)
{
	if (newUnit->getID()==0)
	{
		newUnit->setID(ID);
		ID++;
	}
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
		if (EarthSoliders.isEmpty())
			return nullptr;
		EarthSoliders.dequeue(unit);
	}
		break;
	case earthTank: { 
		if (EarthTanks.isEmpty())
			return nullptr;
		EarthTanks.pop(unit); 
		}
		break;
	case earthGunnery: { 
		if (EarthGunnerys.isEmpty())
			return nullptr;
		EarthGunnerys.dequeue(unit, priorty); //A: visit
		}
		break;
	
	default:
		break;
	}
	return unit;
}

void EarthArmy::Attack()
{
	Unit* unit2;
	//ES Attacks 
	if (EarthSoliders.peek(unit2))
	{
		unit2->Attack();
	}
}

void EarthArmy::Print()
{
	cout << EarthSoliders.getCount()<<" ES  [";
	EarthSoliders.print();
	cout << "]\n";
	cout<<EarthTanks.getCount()<< " ET  [";
	EarthTanks.print();
	cout << "]\n";
	cout << EarthGunnerys.getCount() << " EG  [";
	EarthGunnerys.print();
	cout << "]";
}

EarthArmy::~EarthArmy()
{
}

int EarthArmy::ID = 1;