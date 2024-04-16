#pragma once
#include "Unit.h"
class EarthSolider : public Unit
{
public:
	EarthSolider(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2 );
	~EarthSolider();
};

