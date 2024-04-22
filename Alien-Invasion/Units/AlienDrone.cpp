#include"AlienDrone.h"
#include"../Game class/Game.h"

AlienDrone::AlienDrone(int H, int P, int AC, int tj, Game* Gameptr):Unit(H,P,AC,tj, Gameptr)
{
	Type = alienDrone;
}

void AlienDrone::Attack(Unit* unit2)
{
	LinkedQueue<Unit*> TempList;
	LinkedQueue<Unit*> EnemiesList;
	pGame->GetEnemiesList(Earth,earthTank, this->Attack_Capacity/2, EnemiesList); //Discuss 
	for (int i = 0; i < this->Attack_Capacity / 2; i++)
	{
		
		if (EnemiesList.dequeue(unit2))
		{

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
	pGame->GetEnemiesList(Earth, earthGunnery, this->Attack_Capacity - (this->Attack_Capacity / 2), EnemiesList); //Discuss 


	for (int i = 0; i < this->Attack_Capacity - (this->Attack_Capacity / 2); i++)
	{
		if (EnemiesList.dequeue(unit2))
		{

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
	while (TempList.dequeue(unit2))
	{
		pGame->GetEarthArmyPtr()->AddUnit(unit2);		//return to original list
	}

}

AlienDrone::~AlienDrone()
{
}
