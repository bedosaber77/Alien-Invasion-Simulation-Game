#pragma once
#include "Unit.h"
class HealUnit :  public Unit
{
public:
	HealUnit(double H, double P, int AC, int tj, Game* Gameptr);
	virtual void Attack();
	~HealUnit();
};

