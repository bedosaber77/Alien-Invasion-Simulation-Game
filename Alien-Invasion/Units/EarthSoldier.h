#pragma once
#include "Unit.h"
class EarthSoldier : public Unit
{
private:
	//LinkedQueue<Unit*> EnemiesList;
public:
	EarthSoldier(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2);
	virtual void PrintFight(LinkedQueue<int> EnemiesList);
	~EarthSoldier();
};

