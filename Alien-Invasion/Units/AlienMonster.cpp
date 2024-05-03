#include "AlienMonster.h"
#include <cmath>
#include"../Game class/Game.h"

AlienMonster::AlienMonster(int H, int P, int AC, int tj,  Game* Gameptr) :Unit(H, P, AC, tj, Gameptr)
{
	Type = alienMonster;
}
void AlienMonster::Attack(Unit* unit2)
{
}

void AlienMonster::PrintFight(LinkedQueue<int> EnemiesList)
{
}

AlienMonster::~AlienMonster()
{
}
