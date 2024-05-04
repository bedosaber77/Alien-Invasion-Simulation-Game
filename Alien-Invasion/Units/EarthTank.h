#pragma once
#include "Unit.h"
class EarthTank : public Unit
{
private:
	//LinkedQueue<Unit*> EnemiesList;
public:
	EarthTank(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2);
	~EarthTank();
};

