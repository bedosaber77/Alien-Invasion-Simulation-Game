#include "EarthTank.h"
#include <cmath>
EarthTank::EarthTank(int H, int P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = earthTank;
}
void EarthTank::Attack(Unit* unit2)
{
}

EarthTank::~EarthTank()
{
}
