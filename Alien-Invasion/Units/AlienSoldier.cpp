#include "Aliensoldier.h"
#include"../Game class/Game.h"

AlienSoldier::AlienSoldier(double H, double P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = alienSoldier;
}

void AlienSoldier:: Attack()
{
	Unit* unit2 = nullptr;
	LinkedQueue<Unit*> TempList;
	LinkedQueue<Unit*> EnemiesList;
	

	for (int i = 0; i < this->Attack_Capacity; i++)
	{
		if (i % 2 == 0) {
			unit2 = pGame->GetEnemiesUnit(Earth, earthSoldier); 

			if(!unit2 && pGame->GetCallAlly() && pGame->GetAllyArmyPtr()->GetSUcount() > 0)  //if no earth soldier get a saver unit (if exists)
				unit2 = pGame->GetEnemiesUnit(Ally, saverUnit);
		}
		else {
			if(pGame->GetCallAlly() && pGame->GetAllyArmyPtr()->GetSUcount() > 0)
				unit2 = pGame->GetEnemiesUnit(Ally, saverUnit);  //if ally army is alive get a saver unit
			else
				unit2 = pGame->GetEnemiesUnit(Earth, earthSoldier);  //if no saver units get an earth soldier
		}
		if (unit2)
		{
		
			EnemiesList.enqueue(unit2);
			unit2->setTa(pGame->GetCurrentTime()); //Set Ta (first attacked time)


			double Damage = (this->getHealth() * this->getPower() / 100) /
				sqrt(unit2->getHealth());	//Damage Formula


			unit2->decrementHealth(Damage);  //decrement health of the attacked unit by the damage


			if (unit2->getHealth() > 0.2 * unit2->getIntialHealth())  // Heal Check
			{
				TempList.enqueue(unit2);
			}
			else if (unit2->getHealth() > 0 && unit2->getType() != saverUnit)  //add the unit to uml
			{
				pGame->AddtoUML(unit2);
			}
			else
			{
				pGame->AddtoKilledList(unit2);
			}
		}
		else
		{
			break;
		}
	}

	pGame->PrintFight(this,  EnemiesList);  // printing the fight to the output screen

	while (TempList.dequeue(unit2))  // return to original list
	{
		if (unit2->getType() == saverUnit)
			pGame->GetAllyArmyPtr()->AddUnit(unit2);
		else
		pGame->GetEarthArmyPtr()->AddUnit(unit2);	
	}
}

AlienSoldier::~AlienSoldier()
{
}
