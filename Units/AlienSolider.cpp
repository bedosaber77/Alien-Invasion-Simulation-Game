#include "AlienSolider.h"

AlienSolider::AlienSolider(int H, int P, int AC, int tj):Unit(H, P, AC, tj)
{
	Type = alienSoldier;
}

void AlienSolider::Attack(Unit* unit2)
{
}

AlienSolider::~AlienSolider()
{
}
