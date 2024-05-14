#include "AlienMonster.h"
#include <cmath>
#include"../Game class/Game.h"

AlienMonster::AlienMonster(int H, int P, int AC, int tj,  Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = alienMonster;
	srand(time(0));
}

void AlienMonster::Attack()
{
	Unit* unit2 = nullptr;
	LinkedQueue<Unit*> TempList;
	LinkedQueue<Unit*> EnemiesList;
	LinkedQueue<Unit*> InfectedList;


	bool InfectedRound = false;    // not to kill if u will infect

	for (int i = 0; i < this->Attack_Capacity; i++)
	{
		if (i % 2 == 0)
		{
			unit2 = pGame->GetEnemiesUnit(Earth, earthTank);
			if (!unit2)
			{
				unit2 = pGame->GetEnemiesUnit(Earth, earthSoldier);
			}
		}
		else
		{
			unit2 = pGame->GetEnemiesUnit(Earth, earthSoldier);
			if (!unit2)
			{
				unit2 = pGame->GetEnemiesUnit(Earth, earthTank);
			}
		}

	
		if (unit2)
		{
			//infection process
			if (unit2->getType() == earthSoldier)
			{
				int prob = pGame->getInfectionProb();
				int random = rand() % (4 * prob);

				if (random <= prob)		// to be revisited
				{
					if (!unit2->InfectedBefore() && !unit2->ImmunedBefore())  //check that the unit is not infected before
					{
						unit2->SetInfected(true);
						pGame->IncrementInfectedCount();  //update infected units count in game
						InfectedRound = true;   //Monster doesn't kill the unit after infecting it
						InfectedList.enqueue(unit2);
					}
				}
			}

		//	EnemiesList.enqueue(unit2);
			unit2->setTa(pGame->GetCurrentTime()); //Set Ta (first attacked time)

			if (!InfectedRound)
			{
				EnemiesList.enqueue(unit2);

				int Damage = (this->getHealth() * this->getPower() / 100) /
					sqrt(unit2->getHealth());	//Damage Formula


				unit2->decrementHealth(Damage);


				if (unit2->getHealth() > 0.2 * unit2->getIntialHealth())
				{
					TempList.enqueue(unit2);
				}
				else if (unit2->getHealth() > 0)
				{
					pGame->AddtoUML(unit2);
				}
				else
				{
					unit2->setTd(pGame->GetCurrentTime());		//Destruction Time

					pGame->AddtoKilledList(unit2);
				}
			}
		}
	}

	pGame->PrintFight(this, EnemiesList);
	if(!InfectedList.isEmpty()) pGame->PrintFight(this, InfectedList);

	while (TempList.dequeue(unit2))
	{
		pGame->GetEarthArmyPtr()->AddUnit(unit2);		//return to original list
	}

	while (InfectedList.dequeue(unit2))
	{
		pGame->GetEarthArmyPtr()->AddUnit(unit2);		//return to original list
	}
}

AlienMonster::~AlienMonster()
{
}
