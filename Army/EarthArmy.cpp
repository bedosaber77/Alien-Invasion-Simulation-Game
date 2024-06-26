#include "EarthArmy.h"
#include "../Units/Unit.h"
#include "../Units/EarthGunnery.h"

EarthArmy::EarthArmy()
{
}

void EarthArmy::AddUnit(Unit* newUnit)
{
	//Check if the unit is a new unit or it has returned from the war to set its ID correctly
	if (newUnit->getID() == 0)
	{
		newUnit->setID(ID);
		ID++;
	}

	//Add each unit to its list according to its type 
	if (newUnit->getType() == earthSoldier)
		EarthSoldiers.enqueue(newUnit);
	else if (newUnit->getType() == earthTank)
		EarthTanks.push(newUnit);
	else
	{
		EarthGunnery* earthgunnery = dynamic_cast<EarthGunnery*>(newUnit);
		int priorty = earthgunnery->getCombination();
		EarthGunneries.enqueue(newUnit, priorty);
	}
}

/*
 To remove a unit from its list 
  1- If the List is empty return nullptr
  2- else remove a unit and return it
*/
Unit* EarthArmy::removeUnit(UnitType type)
{
	Unit* unit=nullptr;
	int priorty;
	switch (type)
	{
	case earthSoldier: 
	{
		if (EarthSoldiers.isEmpty())
			return nullptr;
		EarthSoldiers.dequeue(unit);
	}
		break;
	case earthTank: 
	{ 
	    if (EarthTanks.isEmpty())
			return nullptr;
		EarthTanks.pop(unit); 
	}
		break;
	case earthGunnery: 
	{ 
		if (EarthGunneries.isEmpty())
			return nullptr;
		EarthGunneries.dequeue(unit, priorty); 
	}
		break;
	
	default:
		break;
	}
	return unit;
}

void EarthArmy::Attack()
{
}

void EarthArmy::Print()
{
	cout << EarthSoldiers.getCount()<<" ES  [";
	EarthSoldiers.print();
	cout << "]\n";
	cout<<EarthTanks.getCount()<< " ET  [";
	EarthTanks.print();
	cout << "]\n";
	cout << EarthGunneries.getCount() << " EG  [";
	EarthGunneries.print();
	cout << "]";
}

EarthArmy::~EarthArmy()
{
	Unit* DeletedUnit;
	while (!EarthSoldiers.isEmpty())
	{
		EarthSoldiers.dequeue(DeletedUnit);
		delete DeletedUnit;
		DeletedUnit = nullptr;
	}

	while (!EarthTanks.isEmpty())
	{
		EarthTanks.pop(DeletedUnit);
		delete DeletedUnit;
		DeletedUnit = nullptr;
	}

	while (!EarthGunneries.isEmpty())
	{
		int pri;
		EarthGunneries.dequeue(DeletedUnit, pri);
		delete DeletedUnit;
		DeletedUnit = nullptr;
	}	
}

int EarthArmy::ID = 1;