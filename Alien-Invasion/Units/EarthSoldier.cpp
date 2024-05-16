#include<iostream>
#include<string>
using namespace std;
#include "Earthsoldier.h"
#include"../Game Class/Game.h"
EarthSoldier::EarthSoldier(double H, double P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = earthSoldier;
}

void EarthSoldier::Attack()
{
	Unit* unit2 = nullptr;
	LinkedQueue<Unit*> TempList;
	LinkedQueue<Unit*> EnemiesList;

	for (int i = 0; i < this->Attack_Capacity; i++)
	{
		unit2 = (this->InfectedBefore()) ? pGame->GetEnemiesUnit(Earth, earthSoldier) : pGame->GetEnemiesUnit(Alien, alienSoldier);

		if (unit2)
		{
			
			EnemiesList.enqueue(unit2);
			unit2->setTa(pGame->GetCurrentTime()); //Set Ta (first attacked time)


			double Damage = (this->getHealth() * this->getPower() / 100) /
				sqrt(unit2->getHealth());	//Damage Formula


			unit2->decrementHealth(Damage);


			if (unit2->getHealth() > 0)
			{
				TempList.enqueue(unit2);
			}
			else
			{
				pGame->AddtoKilledList(unit2);
			}
		}
	}

	pGame->PrintFight(this,  EnemiesList);

	while (TempList.dequeue(unit2))
	{
		(this->InfectedBefore()) ? pGame->GetEarthArmyPtr()->AddUnit(unit2) : pGame->GetAlienArmyPtr()->AddUnit(unit2);
	}
}


EarthSoldier::~EarthSoldier()
{
}
