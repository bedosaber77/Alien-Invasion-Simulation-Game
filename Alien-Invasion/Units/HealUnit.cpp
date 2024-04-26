#include "HealUnit.h"
#include "../DEFS.h"
HealUnit::HealUnit(int H, int P, int AC, int tj, Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = healUnit;
}

void HealUnit::Attack(Unit* unit2)
{
}
