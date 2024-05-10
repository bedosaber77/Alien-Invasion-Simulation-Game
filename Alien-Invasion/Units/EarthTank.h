#pragma once
#include "Unit.h"
class EarthTank : public Unit
{
private:
	//LinkedQueue<Unit*> EnemiesList;
	bool AttackBoth;
public:
	EarthTank(int H, int P, int AC, int tj, Game* Gameptr);
	virtual bool Attack(Unit* unit2);
	~EarthTank();
};

