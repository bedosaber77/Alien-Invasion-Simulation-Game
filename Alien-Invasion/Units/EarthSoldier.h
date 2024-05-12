#pragma once
#include "Unit.h"
class EarthSoldier : public Unit
{

public:
	EarthSoldier(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2);
	~EarthSoldier();
};

