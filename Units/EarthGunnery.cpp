#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(int H, int P, int AC, int tj) :Unit(H, P, AC, tj)
{
	Type = earthGunnery;
	//power_health     //not sure 
}

void EarthGunnery::Attack(Unit* unit2)
{

}

int EarthGunnery::getCombination()
{
	return this->Health + this->Power;
}

EarthGunnery::~EarthGunnery()
{
}
