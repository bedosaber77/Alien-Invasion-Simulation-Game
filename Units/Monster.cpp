#include "Monster.h"
#include <cmath>
Monster::Monster(int H, int P, int AC, int tj, Game* Gameptr):Unit(H,P,AC,tj, Gameptr)
{
	Type = alienMonster;
}
void Monster::Attack(Unit* unit2)
{
}

Monster::~Monster()
{
}
