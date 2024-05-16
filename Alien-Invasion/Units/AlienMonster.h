#pragma once
#include "Unit.h"
class AlienMonster : public Unit
{
public:
	AlienMonster(double H, double P, int AC, int tj, Game* Gameptr);
	virtual void Attack();
	~AlienMonster();
};

