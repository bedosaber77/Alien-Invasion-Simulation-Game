#pragma once
#include "Unit.h"
class Earthsoldier : public Unit
{
public:
	Earthsoldier(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2);
	~Earthsoldier();
};

