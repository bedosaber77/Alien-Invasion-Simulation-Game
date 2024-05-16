#pragma once
#include "Unit.h"
class AlienSoldier :public Unit
{

public:
	AlienSoldier(double H, double P, int AC, int tj, Game* Gameptr);
	virtual void Attack();
	~AlienSoldier();
};

