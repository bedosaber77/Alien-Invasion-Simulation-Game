#include "EarthGunnery.h"
#include"../Game class/Game.h"

EarthGunnery::EarthGunnery(int H, int P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = earthGunnery;
}

void EarthGunnery::Attack(Unit* unit2)
{
	Unit* DroneUnit, *MonsterUnit;
	LinkedQueue<Unit*> TempList;
	LinkedQueue<Unit*> DroneEnemiesList;
	LinkedQueue<Unit*> MonsterEnemiesList;

	//Assume Attack Capacity is even for now
	pGame->GetEnemiesList(Alien, alienMonster, this->Attack_Capacity / 2, MonsterEnemiesList);
	pGame->GetEnemiesList(Alien, alienDrone, this->Attack_Capacity / 2, DroneEnemiesList);

	for (int i = 0; i < Attack_Capacity / 2; i++)
	{
		if (MonsterEnemiesList.dequeue(MonsterUnit))
		{
			MonsterUnit->setTa(pGame->GetCurrentTime()); //Set Ta (first attacked time)

			int Damage = (this->getHealth() * this->getPower() / 100) /
				sqrt(MonsterUnit->getHealth());	//Damage Formula

			MonsterUnit->decrementHealth(Damage);

			if (MonsterUnit->getHealth() > 0)
			{
				TempList.enqueue(MonsterUnit);
			}
			else if (MonsterUnit->getHealth() <= 0)
			{
				unit2->setTd(pGame->GetCurrentTime()); // Destruction Time

				pGame->AddtoKilledList(MonsterUnit);
			}
		}
	}

	for (int i = 0; i < Attack_Capacity / 2; i++)
	{
		if (DroneEnemiesList.dequeue(DroneUnit))
		{
			DroneUnit->setTa(pGame->GetCurrentTime()); //Set Ta (first attacked time)

			int Damage = (this->getHealth() * this->getPower() / 100) /
				sqrt(DroneUnit->getHealth());	//Damage Formula

			DroneUnit->decrementHealth(Damage);

			if (DroneUnit->getHealth() > 0)	
			{
				TempList.enqueue(DroneUnit);
			}
			else if (DroneUnit->getHealth() <= 0) 
			{
				unit2->setTd(pGame->GetCurrentTime()); // Destruction Time

				pGame->AddtoKilledList(DroneUnit);
			}
		}
	}

	while (TempList.dequeue(unit2))
	{
		if(unit2->getType() == alienMonster)
		     pGame->GetAlienArmyPtr()->AddUnit(unit2);		//return to original list
		else if(unit2->getType() == alienDrone)
	     	 pGame->GetAlienArmyPtr()->AddUnit(unit2);		//return to original list
	}
}

//Function to return highest Health-Power combination
int EarthGunnery::getCombination() const
{
	return this->Health + this->Power;
}

EarthGunnery::~EarthGunnery()
{
}
