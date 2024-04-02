#pragma once
#include "Unit.h"
class AlienSolider :public Unit
{
public:
	AlienSolider(int H, int P, int AC, int tj);
	virtual void Attack(Unit* unit2);
	~AlienSolider();
};

