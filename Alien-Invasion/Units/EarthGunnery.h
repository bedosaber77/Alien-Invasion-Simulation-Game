#pragma once
#include "Unit.h"
class EarthGunnery : public Unit
{
public:
	EarthGunnery(int H, int P, int AC, int tj, Game* Gameptr);

	virtual bool Attack(Unit* unit2);
	int getCombination() const; //EG priority formula

	~EarthGunnery();
};