#pragma once
#include "Unit.h"
class Aliensoldier :public Unit
{
public:
	Aliensoldier(int H, int P, int AC, int tj);
	virtual void Attack(Unit* unit2);
	~Aliensoldier();
};

