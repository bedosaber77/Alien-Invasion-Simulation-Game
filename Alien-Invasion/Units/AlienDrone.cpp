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

	

	for (int i = 0; i < this->Attack_Capacity; i++)   // ENEMIES LIST IS EMPTY >>BREAK;
	{
		if (i % 2 == 0)
		{
			unit2 = pGame->GetEnemiesUnit(Earth, earthTank);
			if(!unit2)
			{
				unit2 = pGame->GetEnemiesUnit(Earth, earthGunnery);
			}
		}
		else
		{
			unit2 = pGame->GetEnemiesUnit(Earth, earthGunnery);
			if (!unit2)
			{
				unit2 = pGame->GetEnemiesUnit(Earth, earthTank);
			}	
		}


		if (unit2)
		{
		
			EnemiesList.enqueue(unit2->getID());
			unit2->setTa(pGame->GetCurrentTime()); //Set Ta (first attacked time)


			int Damage = (this->getHealth() * this->getPower() / 100) /
				sqrt(unit2->getHealth());	//Damage Formula


			unit2->decrementHealth(Damage);


			if (unit2->getHealth() > 0.2 * unit2->getIntialHealth())  // Heal Check
			{
				TempList.enqueue(unit2);
			}
			else if (unit2->getHealth() > 0&&unit2->getType()==earthTank)
			{
				pGame->AddtoUML(unit2);
			}
			else
			{
				unit2->setTd(pGame->GetCurrentTime());		//Destruction Time

				pGame->AddtoKilledList(unit2);
			}
		}
		else
		{
			break;
		}
		// GET EG TO ATTACK
		
	}

	pGame->PrintFight(this, this->getType(), EnemiesList);

	while (TempList.dequeue(unit2))
	{
		pGame->GetEarthArmyPtr()->AddUnit(unit2);		//return to original list
	}

	
}


AlienDrone::~AlienDrone()
{
}
