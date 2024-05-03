#include"AlienDrone.h"
#include"../Game class/Game.h"

AlienDrone::AlienDrone(int H, int P, int AC, int tj, Game* Gameptr):Unit(H,P,AC,tj, Gameptr)
{
	Type = alienDrone;
}

void AlienDrone::Attack(Unit* unit2)
{
	LinkedQueue<Unit*> TempList;
	LinkedQueue<int> EnemiesList;
	//pGame->GetEnemiesList(Earth, earthTank, this->Attack_Capacity/2, EnemiesList); //Discuss 
	//pGame->GetEnemiesList(Earth, earthGunnery, this->Attack_Capacity - (this->Attack_Capacity / 2), EnemiesList);
	//PrintFight(EnemiesList);


	for (int i = 0; i < this->Attack_Capacity / 2; i++)
	{
		unit2 = pGame->GetEnemiesUnit(Earth,earthTank);
		if (unit2)
		{
			EnemiesList.enqueue(unit2->getID());
			unit2->setTa(pGame->GetCurrentTime()); //Set Ta (first attacked time)


			int Damage = (this->getHealth() * this->getPower() / 100) /
				sqrt(unit2->getHealth());	//Damage Formula


			unit2->decrementHealth(Damage);


			if (unit2->getHealth() > 0.2*unit2->getIntialHealth())
			{
				TempList.enqueue(unit2);
			}
			else if (unit2->getHealth() > 0 && (unit2->getType() == earthSoldier || unit2->getType() == earthTank))
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
 

	for (int i = 0; i < this->Attack_Capacity - (this->Attack_Capacity / 2); i++)
	{
		unit2 = pGame->GetEnemiesUnit(Earth, earthGunnery);
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
	//pGame->PrintFight(this, this->getType(), TempList);
	//PrintFight(TempList);
	PrintFight(EnemiesList);
	while (TempList.dequeue(unit2))
	{
		pGame->GetEarthArmyPtr()->AddUnit(unit2);		//return to original list
	}
}

void AlienDrone::PrintFight(LinkedQueue<int> EnemiesList)
{
	cout << "AD " << this->getID() << " shots [";
	EnemiesList.print();
	cout << "]" << endl;
}

AlienDrone::~AlienDrone()
{
}
