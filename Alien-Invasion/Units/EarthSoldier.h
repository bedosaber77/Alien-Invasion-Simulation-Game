#pragma once
#include "Unit.h"
class EarthSoldier : public Unit
{

public:
	EarthSoldier(int H, int P, int AC, int tj, Game* Gameptr);
	virtual bool Attack(Unit* unit2);
	~EarthSoldier();
};

