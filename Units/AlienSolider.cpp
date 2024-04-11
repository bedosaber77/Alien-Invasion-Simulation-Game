#include "AlienSolider.h"
//#include"../Alien-Invasion/Game.h"
AlienSolider::AlienSolider(int H, int P, int AC, int tj, Game* Gameptr):Unit(H, P, AC, tj, Gameptr)
{
	Type = alienSolider;
}

void AlienSolider::Attack(Unit* unit2)
{
}

AlienSolider::~AlienSolider()
{
}
