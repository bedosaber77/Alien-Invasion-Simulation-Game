#pragma once
#include "Unit.h"
class SaverUnit : public Unit
{
public:
	SaverUnit(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack();
	~SaverUnit();
};

