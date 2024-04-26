#pragma once
#include "Unit.h"
class AlienSoldier :public Unit
{
private:
	//LinkedQueue<Unit*> EnemiesList;
public:
	AlienSoldier(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2);
	virtual void PrintFight(LinkedQueue<Unit*> EnemiesList);
	~AlienSoldier();
};

