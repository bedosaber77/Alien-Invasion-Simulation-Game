#include "AlienSolider.h"

AlienSolider::AlienSolider(int H, int P, int AC, int tj):Unit(H, P, AC, tj)
{
	this->setAleinID();
	Type = alienSolider;
}

void AlienSolider::Attack(Unit* unit2)
{
}

AlienSolider::~AlienSolider()
{
}
