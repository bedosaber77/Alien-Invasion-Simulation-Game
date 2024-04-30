#include "HealUnit.h"
#include "../Game Class/Game.h"
#include "../DEFS.h"
#include <cmath>
HealUnit::HealUnit(int H, int P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = healUnit;
}

void HealUnit::Attack(Unit* unit2)
{
	LinkedQueue<Unit*> TempList;
	for (int i = 0; i < this->Attack_Capacity; i++)
	{
		unit2 = pGame->getUnitToHeal();
		if (unit2) {
			if (pGame->GetCurrentTime() - unit2->getTH() == 10)
			{
				pGame->AddtoKilledList(unit2);
			}
			else
			{
				int incHeal = this->Power * (this->Health / 100) / sqrt(unit2->getHealth());
				unit2->incrementHealth(incHeal);
				if (unit2->getHealth() > 0.2 * unit2->getIntialHealth())
				{
					pGame->GetEarthArmyPtr()->AddUnit(unit2);
					unit2->ExitUML();
				}
				else
					TempList.enqueue(unit2);
			}
		}
	}
	while (!TempList.isEmpty())
	{
		Unit* unit;
		TempList.dequeue(unit);
		pGame->AddtoUML(unit);
	}
	pGame->AddtoKilledList(this);
}

HealUnit::~HealUnit()
{
}
