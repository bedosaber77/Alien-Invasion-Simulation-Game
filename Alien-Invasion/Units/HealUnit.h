#pragma once
#include "Unit.h"
class HealUnit :  public Unit
{
public:
	HealUnit(int H, int P, int AC, int tj, Game* Gameptr);
	virtual bool Attack(Unit* unit2);
	~HealUnit();
};

