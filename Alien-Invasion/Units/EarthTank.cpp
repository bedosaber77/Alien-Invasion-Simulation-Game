#include "EarthTank.h"
#include <cmath>
#include"../Game class/Game.h"

EarthTank::EarthTank(double H, double P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = earthTank;
	AttackBoth = false;  //it won't attack alien soldiers unless its true
}

void EarthTank::Attack()
{
	Unit* unit2 = nullptr;
	LinkedQueue<Unit*> TempList;
	LinkedQueue<Unit*> EnemiesList;

	//if no of earth soldiers / no of alien soldiers < 0.3 -> it attacks both
	if (pGame->GetEarthArmyPtr()->GetEScount() < 0.3 * pGame->GetAlienArmyPtr()->GetAScount())
			AttackBoth = true;
	//attack both remain true until the no of earth soldiers / no of alien soldiers > 0.8
	if (pGame->GetEarthArmyPtr()->GetEScount() >= 0.8 * pGame->GetAlienArmyPtr()->GetAScount())
			AttackBoth = false;

	for (int i = 0; i < this->Attack_Capacity; i++)  // ENEMIES LIST IS EMPTY ->> BREAK;
	{
		if (i % 2 == 0)  // alternate between the two units to attack
		{
			unit2 = pGame->GetEnemiesUnit(Alien, alienMonster);
			if (!unit2 && AttackBoth)  //if no alien monster and it can attack both get an alien soldier
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

			if (!unit2)  //if no alien soldier or it can't attack both get alien monster
			{
				unit2 = pGame->GetEnemiesUnit(Alien, alienMonster);
			}
		}

		if (unit2)
		{
			
			EnemiesList.enqueue(unit2);
			unit2->setTa(pGame->GetCurrentTime()); //Set Ta (first attacked time)


			double Damage = (this->getHealth() * this->getPower() / 100) /
				sqrt(unit2->getHealth());	//Damage Formula


			unit2->decrementHealth(Damage);  //decrement health of the attacked unit by the damage


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
	pGame->PrintFight(this, EnemiesList);  // printing the fight to the output screen

	while (TempList.dequeue(unit2))  //return to original list
	{
		pGame->GetAlienArmyPtr()->AddUnit(unit2);		
	}
	
}
EarthTank::~EarthTank()
{
}
