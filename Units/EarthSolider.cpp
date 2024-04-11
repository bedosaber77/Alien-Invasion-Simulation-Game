#include<iostream>
#include<string>
using namespace std;
#include "EarthSolider.h"
#include"../Alien-Invasion/Game.h"
EarthSolider::EarthSolider(int H, int P, int AC, int tj, Game* Gameptr):Unit(H,P,AC,tj, Gameptr)
{
	Type = earthSoliders;
}

void EarthSolider::Attack(Unit* unit2)
{
	LinkedQueue<Unit*> TempList;
	LinkedQueue<Unit*> EnemiesList;

	for (int i = 0; i < this->Attack_Capacity; i++)
	{
		pGame->GetAlienArmyPtr()->GetEnemiesList(alienSolider, this->Attack_Capacity);
		if (EnemiesList.dequeue(unit2))
		{

			unit2->setTa(pGame->GetCurrentTime()); //Set Ta (first attacked time)


			int Damage = (this->getHealth() * this->getPower() / 100) /
				sqrt(unit2->getHealth());	//Damage Formula


			unit2->setHealth(unit2->getHealth() - Damage);


			if (unit2 && unit2->getHealth() > 0)	//not needed ,but for more safety now
			{
				TempList.enqueue(unit2);
			}
			else if(unit2 && unit2->getHealth() <= 0) //not needed ,but for more safety now
			{
				pGame->AddtoKilledList(unit2);
			}
		}
	}
	while (TempList.dequeue(unit2))
	{
		pGame->GetAlienArmyPtr()->AddUnit(unit2);		//return to original list
	}

}

EarthSolider::~EarthSolider()
{
}
