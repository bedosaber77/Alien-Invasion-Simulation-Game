#include "EarthArmy.h"
#include "../Units/Unit.h"
#include "../Units/EarthGunnery.h"

EarthArmy::EarthArmy()
{
	HealedUnits = 0;
}

//==================================================================================//
//								Add / Remove Functions	     						//
//==================================================================================//


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

	else if(newUnit->getType() == earthGunnery)
	{
		EarthGunnery* earthgunnery = dynamic_cast<EarthGunnery*>(newUnit);
		int priorty = earthgunnery->getCombination();
		EarthGunneries.enqueue(newUnit, priorty);
	}
	else 
	{
		HL.push(newUnit);
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
	case healUnit:
	{
		if (HL.isEmpty())
			return nullptr;
		HL.pop(unit);
	}
	default:
		break;
	}
	return unit;
}

//==================================================================================//
//							     Getters Functions	          						//
//==================================================================================//
int EarthArmy::GetEScount()const 
{
	return EarthSoldiers.getCount();
}

int EarthArmy::GetEGcount() const
{
	return EarthGunneries.getCount();
}

int EarthArmy::GetETcount()const
{
	return EarthTanks.getCount();
}

int EarthArmy::GetHUcount()const
{
	return HL.getCount();
}

int EarthArmy::GetID()const
{
	return ID;
}


//==================================================================================//
//							      	Fighting Functions       						//
//==================================================================================//


void EarthArmy::Attack()
{
	Unit* unit2=nullptr;


	//ES Attacks 
	if (EarthSoldiers.dequeue(unit2))
	{
	//	if (unit2->InfectedBefore()) EarthSoldiers.dequeue(unit2);
		unit2->Attack();
	    EarthSoldiers.enqueue(unit2);
	}
	
	//ET Attacks
	if(EarthTanks.peek(unit2))
	{
		 unit2->Attack() ;
	}

	//EG Attacks
	int pri;
	if (EarthGunneries.peek(unit2, pri))
	{
	    unit2->Attack();
	}

	//HU Heals
	if (HL.peek(unit2))
	{
		unit2->Attack();
	}

	return ;

}

void EarthArmy::Print()const
{
	cout << EarthSoldiers.getCount()<<" ES  [";
	EarthSoldiers.print();
	cout << "]\n";
	cout<<EarthTanks.getCount()<< " ET  [";
	EarthTanks.print();
	cout << "]\n";
	cout << EarthGunneries.getCount() << " EG  [";
	EarthGunneries.print();
	cout << "]\n";
	cout << HL.getCount() << " HU  [";
	HL.print();
	cout << "]";
}

void EarthArmy::SpeardInfection()
{
	int A = rand() % 100 + 1;
	if(A <= 2)
	{
		int B = (EarthSoldiers.getCount() == 0) ? 0 : rand() % EarthSoldiers.getCount();
		LinkedQueue<Unit*> Temp;
		Unit* unit=nullptr;
		for(int i = 0; i < B;i++)
		{
			EarthSoldiers.dequeue(unit);
			Temp.enqueue(unit);
		}
		EarthSoldiers.peek(unit);
		if(unit) unit->SetInfected(true);
		
		while(Temp.dequeue(unit))
			EarthSoldiers.enqueue(unit);
	}

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