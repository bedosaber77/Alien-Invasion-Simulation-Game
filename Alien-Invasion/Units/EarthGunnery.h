#pragma once
#include "Unit.h"
class EarthGunnery : public Unit
{
public:
	EarthGunnery(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2);
	int getCombination() const;
	~EarthGunnery();
};