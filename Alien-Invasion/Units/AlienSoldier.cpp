#include "Aliensoldier.h"
#include"../Game class/Game.h"

AlienSoldier::AlienSoldier(int H, int P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = alienSoldier;
}

void AlienSoldier:: Attack(Unit* unit2)
{
	LinkedQueue<Unit*> TempList;
	LinkedQueue<Unit*> EnemiesList;
	pGame->GetEnemiesList(Earth, earthSoldier, this->Attack_Capacity, EnemiesList); //Discuss 


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
				pGame->OutputFile(unit2);
			}
		}
	}

	pGame->PrintFight(this, this->getType(), TempList);
	//PrintFight(TempList);
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
