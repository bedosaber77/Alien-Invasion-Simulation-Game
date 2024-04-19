#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(int H, int P, int AC, int tj) :Unit(H, P, AC, tj)
{
	Type = earthGunnery;
}

void EarthGunnery::Attack(Unit* unit2)
{

}

//Function to return highest Health-Power combination
int EarthGunnery::getCombination() const
{
	return this->Health + this->Power;
}

EarthGunnery::~EarthGunnery()
{
}
