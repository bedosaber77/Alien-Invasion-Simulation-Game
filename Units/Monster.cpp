#include "Monster.h"
#include <cmath>
Monster::Monster(int H, int P, int AC, int tj):Unit(H,P,AC,tj)
{
	Type = alienMonster;
}
void Monster::Attack(Unit* unit2)
{
}

Monster::~Monster()
{
}
