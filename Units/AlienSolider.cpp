#include "AlienSolider.h"
#include"../Alien-Invasion/Game.h"
AlienSolider::AlienSolider(int H, int P, int AC, int tj, Game* Gameptr):Unit(H, P, AC, tj, Gameptr)
{
	Type = alienSolider;
}

void AlienSolider::Attack(Unit* unit2)
{
	LinkedQueue<Unit*> TempList;
	LinkedQueue<Unit*> EnemiesList;
	pGame->GetEnemiesList(Earth, earthSoliders, this->Attack_Capacity, EnemiesList); //Discuss 

	for (int i = 0; i < this->Attack_Capacity; i++)
	{
		if (EnemiesList.dequeue(unit2))
		{

			unit2->setTa(pGame->GetCurrentTime()); //Set Ta (first attacked time)


			int Damage = (this->getHealth() * this->getPower() / 100) /
				sqrt(unit2->getHealth());	//Damage Formula


			unit2->decrementHealth(Damage);


			if (unit2 && unit2->getHealth() > 0)	//not needed ,but for more safety now
			{
				TempList.enqueue(unit2);
			}
			else if (unit2 && unit2->getHealth() <= 0) //not needed ,but for more safety now
			{
				unit2->setTd(pGame->GetCurrentTime()); // Destruction Time

				pGame->AddtoKilledList(unit2);
			}
		}
	}



	while (TempList.dequeue(unit2))
	{
		pGame->GetEarthArmyPtr()->AddUnit(unit2);		//return to original list
	}
}

AlienSolider::~AlienSolider()
{
}
