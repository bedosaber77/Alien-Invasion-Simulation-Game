#include "EarthTank.h"
#include <cmath>
#include"../Game class/Game.h"

EarthTank::EarthTank(int H, int P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = earthTank;
}
void EarthTank::Attack(Unit* unit2)
{
	LinkedQueue<Unit*> TempList;
	LinkedQueue<int> EnemiesList;

	for (int i = 0; i < this->Attack_Capacity; i++)
	{
		unit2 = pGame->GetEnemiesUnit(Alien, alienMonster);
		if (unit2)
		{

		}
	}
}
EarthTank::~EarthTank()
{
}
