#include<iostream>
#include<string>
using namespace std;
#include "Earthsoldier.h"
#include"../Game Class/Game.h"
EarthSoldier::EarthSoldier(int H, int P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = earthSoldier;
}

void EarthSoldier::Attack(Unit* unit2)
{
	LinkedQueue<Unit*> TempList;
	LinkedQueue<int> EnemiesList;

	

	for (int i = 0; i < this->Attack_Capacity; i++)
	{
		unit2 = pGame->GetEnemiesUnit(Alien, alienSoldier);
		if (unit2)
		{
			
			EnemiesList.enqueue(unit2->getID());
			unit2->setTa(pGame->GetCurrentTime()); //Set Ta (first attacked time)


			int Damage = (this->getHealth() * this->getPower() / 100) /
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

	pGame->PrintFight(this, this->getType(), EnemiesList);

	while (TempList.dequeue(unit2))
	{
		pGame->GetAlienArmyPtr()->AddUnit(unit2);		//return to original list
	}
}


EarthSoldier::~EarthSoldier()
{
}
