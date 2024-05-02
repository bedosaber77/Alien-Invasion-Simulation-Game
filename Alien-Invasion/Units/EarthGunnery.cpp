#include "EarthGunnery.h"
#include"../Game class/Game.h"

EarthGunnery::EarthGunnery(int H, int P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = earthGunnery;
}

void EarthGunnery::Attack(Unit* unit2)
{
	LinkedQueue<Unit*> TempList;
	//LinkedQueue<Unit*> EnemiesList;

	////Assume Attack Capacity is even for now
	//pGame->GetEnemiesList(Alien, alienMonster, this->Attack_Capacity / 2, EnemiesList);
	//pGame->GetEnemiesList(Alien, alienDrone, this->Attack_Capacity - (this->Attack_Capacity / 2), EnemiesList);
	//PrintFight(EnemiesList);


	for (int i = 0; i < this->Attack_Capacity; i++)
	{
		unit2 = pGame->GetAlienArmyPtr()->removeUnit(alienMonster);
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

	int i = 1;
	while (TempList.dequeue(unit2))
	{
		if (unit2->getType() == alienDrone)
		{
			pGame->GetAlienArmyPtr()->AddUnit(unit2, i % 2);		// Add from front then from back
			i++;
		}
		else
		{
			pGame->GetAlienArmyPtr()->AddUnit(unit2);
		}
	}
}

void EarthGunnery::PrintFight(LinkedQueue<Unit*> EnemiesList)
{
	cout << "EG " << this->getID() << " shots [";
	EnemiesList.print();
	cout << "]" << endl;
}


//Function to return highest Health-Power combination
int EarthGunnery::getCombination() const
{
	return this->Health + this->Power;
}

EarthGunnery::~EarthGunnery()
{
}
