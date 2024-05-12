#include "EarthTank.h"
#include <cmath>
#include"../Game class/Game.h"

EarthTank::EarthTank(int H, int P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = earthTank;
	AttackBoth = false;
}

void EarthTank::Attack()
{
	Unit* unit2 = nullptr;
	LinkedQueue<Unit*> TempList;
	LinkedQueue<int> EnemiesList;

	
	
	if (pGame->GetEarthArmyPtr()->GetEScount() < 0.3 * pGame->GetAlienArmyPtr()->GetAScount())
			AttackBoth = true;
	if (pGame->GetEarthArmyPtr()->GetEScount() >= 0.8 * pGame->GetAlienArmyPtr()->GetAScount())
			AttackBoth = false;

	for (int i = 0; i < this->Attack_Capacity; i++)
	{
		if (i % 2 == 0)
		{
			unit2 = pGame->GetEnemiesUnit(Alien, alienMonster);
			if (!unit2 && AttackBoth)
			{
				unit2 = pGame->GetEnemiesUnit(Alien, alienSoldier);
			}
		}
		else 
		{
			if (AttackBoth)
			{
				unit2 = pGame->GetEnemiesUnit(Alien, alienSoldier);
			}
			else
				unit2 = nullptr;

			if (!unit2)
			{
				unit2 = pGame->GetEnemiesUnit(Alien, alienMonster);
			}
		}

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
				unit2->setTd(pGame->GetCurrentTime());		//Destruction Time

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
EarthTank::~EarthTank()
{
}
