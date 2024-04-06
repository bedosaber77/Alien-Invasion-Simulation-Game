#include "EarthTank.h"
#include <cmath>
EarthTank::EarthTank(int H, int P, int AC, int tj) :Unit(H, P, AC, tj)
{
	Type = earthTank;
}
void EarthTank::Attack(Unit* unit2)
{
}

EarthTank::~EarthTank()
{
}
