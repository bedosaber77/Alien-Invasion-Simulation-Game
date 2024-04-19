#include "AlienMonster.h"
#include <cmath>

AlienMonster::AlienMonster(int H, int P, int AC, int tj):Unit(H,P,AC,tj)
{
	Type = alienMonster;
}
void AlienMonster::Attack(Unit* unit2)
{
}

AlienMonster::~AlienMonster()
{
}
