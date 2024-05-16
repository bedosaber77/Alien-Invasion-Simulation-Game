#pragma once
#include "Unit.h"
class EarthTank : public Unit
{
private:
	// Handle if it attacks both AS& AM
	bool AttackBoth;
public:

	EarthTank(double H, double P, int AC, int tj, Game* Gameptr);
	virtual void Attack();
	~EarthTank();
};

