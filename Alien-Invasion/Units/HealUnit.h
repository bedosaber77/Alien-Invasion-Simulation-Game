#pragma once
#include "Unit.h"
class HealUnit :  public Unit
{
public:
	HealUnit(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2);
	virtual void PrintFight(LinkedQueue<int> EnemiesList);
	~HealUnit();
};
