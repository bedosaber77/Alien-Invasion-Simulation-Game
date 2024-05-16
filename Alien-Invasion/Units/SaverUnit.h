#pragma once
#include "Unit.h"
class SaverUnit : public Unit
{
public:
	SaverUnit(double H, double P, int AC, int tj, Game* Gameptr);
	virtual void Attack();
	~SaverUnit();
};

