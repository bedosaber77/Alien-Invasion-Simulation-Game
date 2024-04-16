#include "AlienMonster.h"
#include <cmath>

AlienMonster::AlienMonster(int H, int P, int AC, int tj,  Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = alienMonster;
}
void AlienMonster::Attack(Unit* unit2)
{
}

AlienMonster::~AlienMonster()
{
}
