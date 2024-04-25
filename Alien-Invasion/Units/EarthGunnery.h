#pragma once
#include "Unit.h"
class EarthGunnery : public Unit
{
private:
	//LinkedQueue<Unit*> EnemiesList;
public:
	EarthGunnery(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2);
	virtual void PrintFight(LinkedQueue<Unit*> EnemiesList);
	int getCombination() const;
	~EarthGunnery();
};