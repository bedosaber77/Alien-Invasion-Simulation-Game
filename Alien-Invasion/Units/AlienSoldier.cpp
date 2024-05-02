#include "Aliensoldier.h"
#include"../Game class/Game.h"

AlienSoldier::AlienSoldier(int H, int P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = alienSoldier;
}

void AlienSoldier:: Attack(Unit* unit2)
{
	LinkedQueue<Unit*> TempList;
	//LinkedQueue<Unit*> EnemiesList;
	//pGame->GetEnemiesList(Earth, earthSoldier, this->Attack_Capacity, EnemiesList); //Discuss 
	//PrintFight(EnemiesList);

	for (int i = 0; i < this->Attack_Capacity; i++)
	{
		unit2 = pGame->GetEnemiesUnit(Earth, earthSoldier);
		if (unit2)
		{

			unit2->setTa(pGame->GetCurrentTime()); //Set Ta (first attacked time)


			int Damage = (this->getHealth() * this->getPower() / 100) /
				sqrt(unit2->getHealth());	//Damage Formula


			unit2->decrementHealth(Damage);


			if (unit2->getHealth() > 0.2 * unit2->getIntialHealth())
			{
				TempList.enqueue(unit2);
			}
			else if (unit2->getHealth() > 0 && (unit2->getType() == earthSoldier || unit2->getType() == earthTank))
				pGame->AddtoUML(unit2);
			else
			{
				unit2->setTd(pGame->GetCurrentTime());		//Destruction Time

				pGame->AddtoKilledList(unit2);
			}
		}
	}



	while (TempList.dequeue(unit2))
	{
		pGame->GetEarthArmyPtr()->AddUnit(unit2);		//return to original list
	}
}

void AlienSoldier::PrintFight(LinkedQueue<Unit*> EnemiesList)
{
	cout << "AS " << this->getID() << " shots [";
	EnemiesList.print();
	cout << "]" << endl;
}

AlienSoldier::~AlienSoldier()
{
}
