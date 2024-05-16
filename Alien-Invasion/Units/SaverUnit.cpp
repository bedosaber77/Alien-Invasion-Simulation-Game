#include "SaverUnit.h"
#include"../Game Class/Game.h"

SaverUnit::SaverUnit(double H, double P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
    Type = saverUnit;
}

void SaverUnit::Attack()
{
    Unit* unit2 = nullptr;
    LinkedQueue<Unit*> TempList;    
    LinkedQueue<Unit*> EnemiesList;

    for (int i = 0; i < this->Attack_Capacity; i++)
    {
       unit2 = pGame->GetEnemiesUnit(Alien, alienSoldier);

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
                pGame->AddtoKilledList(unit2);
            }
        }
    }

    pGame->PrintFight(this, EnemiesList); // printing the fight to the output screen

    while (TempList.dequeue(unit2))  // return to original list
    {
       pGame->GetAlienArmyPtr()->AddUnit(unit2);
    }
}


SaverUnit::~SaverUnit()
{
}
