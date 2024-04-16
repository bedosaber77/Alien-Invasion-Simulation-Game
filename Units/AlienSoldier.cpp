#include "Aliensoldier.h"

Aliensoldier::Aliensoldier(int H, int P, int AC, int tj):Unit(H, P, AC, tj)
{
	Type = alienSoldier;
}

void Aliensoldier::Attack(Unit* unit2)
{
}

Aliensoldier::~Aliensoldier()
{
}
