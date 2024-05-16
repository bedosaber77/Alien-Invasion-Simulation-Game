#include "EarthGunnery.h"
#include"../Game class/Game.h"

EarthGunnery::EarthGunnery(double H, double P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = earthGunnery;
}

void EarthGunnery::Attack()
{
	Unit* unit2 = nullptr;
	LinkedQueue<Unit*> TempList;
	LinkedQueue<Unit*> EnemiesList;
	
	
	bool IntoFront = false;  //bool to get one dron from front and one from back 


	for (int i = 0; i < this->Attack_Capacity; i++)  // ENEMIES LIST IS EMPTY ->> BREAK;
	{
		if (i % 2 == 0)   // alternate between the two units to attack
		{
			unit2 = pGame->GetEnemiesUnit(Alien, alienMonster);  
			if(!unit2)  //if no alien monster get an alien drone
			{
				unit2 = pGame->GetEnemiesUnit(Alien, alienDrone, IntoFront);
                IntoFront = !IntoFront;
			}
		}
		else
		{
			unit2 = pGame->GetEnemiesUnit(Alien, alienDrone, IntoFront);
			IntoFront = !IntoFront;

			if (!unit2)  //if no alien drone get an alien monster
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


			if (unit2->getHealth() > 0)   // Heal Check
			{
				TempList.enqueue(unit2);
			}
			else
			{
				pGame->AddtoKilledList(unit2);
			}
		}
		else
			break;
	}
	

	pGame->PrintFight(this,EnemiesList);  // printing the fight to the output screen

	int i = 1;
	while (TempList.dequeue(unit2))  // return to original list
	{
		if (unit2->getType() == alienDrone)   // return to original list
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

//Function to return highest Health-Power combination
int EarthGunnery::getCombination() const
{
	return this->Health + this->Power;
}

EarthGunnery::~EarthGunnery()
{
}
