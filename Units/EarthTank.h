#pragma once
#include "Unit.h"
class EarthTank : public Unit
{
public:
	EarthTank(int H, int P, int AC, int tj);
	virtual void Attack(Unit* unit2);
	~EarthTank();
};

