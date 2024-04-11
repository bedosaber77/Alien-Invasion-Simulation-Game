#pragma once
#include "Unit.h"
class Monster : public Unit
{
public:

	Monster(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2);
	~Monster();
};

