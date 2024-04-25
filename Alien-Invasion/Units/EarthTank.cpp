#include "EarthTank.h"
#include <cmath>
#include"../Game class/Game.h"

EarthTank::EarthTank(int H, int P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = earthTank;
}
void EarthTank::Attack(Unit* unit2)
{
}

void EarthTank::PrintFight(LinkedQueue<Unit*> EnemiesList) 
{
}

EarthTank::~EarthTank()
{
}
