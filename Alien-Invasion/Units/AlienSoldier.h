#pragma once
#include "Unit.h"
class AlienSoldier :public Unit
{

public:
	AlienSoldier(int H, int P, int AC, int tj, Game* Gameptr);
	virtual bool Attack(Unit* unit2);
	~AlienSoldier();
};

