#pragma once
#include "Unit.h"
class EarthGunnery : public Unit
{
public:
	EarthGunnery(int H, int P, int AC, int tj, Game* Gameptr);

	virtual void Attack();
	int getCombination() const; //EG priority formula

	~EarthGunnery();
};