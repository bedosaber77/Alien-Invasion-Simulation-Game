#pragma once
#include "Unit.h"
class AlienSoldier :public Unit
{
public:
	AlienSoldier(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2);
	~AlienSoldier();
};

