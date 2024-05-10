#pragma once
#include "Unit.h"
class AlienMonster : public Unit
{
public:
	AlienMonster(int H, int P, int AC, int tj, Game* Gameptr);
	virtual bool Attack(Unit* unit2);
	~AlienMonster();
};

