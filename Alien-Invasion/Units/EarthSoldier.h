#pragma once
#include "Unit.h"
class EarthSoldier : public Unit
{

public:
	EarthSoldier(double H, double P, int AC, int tj, Game* Gameptr);
	virtual void Attack();
	~EarthSoldier();
};

