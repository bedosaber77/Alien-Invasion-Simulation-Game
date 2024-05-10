#pragma once
#include "Unit.h"
class AlienSoldier :public Unit
{
private:
	//LinkedQueue<Unit*> EnemiesList;
public:
	AlienSoldier(int H, int P, int AC, int tj, Game* Gameptr);
	virtual bool Attack(Unit* unit2);
	~AlienSoldier();
};

