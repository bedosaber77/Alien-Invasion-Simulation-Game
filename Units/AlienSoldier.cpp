#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(int H, int P, int AC, int tj):Unit(H, P, AC, tj)
{
	Type = alienSoldier;
}

void AlienSoldier::Attack(Unit* unit2)
{
}

AlienSoldier::~AlienSoldier()
{
}
