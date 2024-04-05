#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(int H, int P, int AC, int tj) :Unit(H, P, AC, tj)
{
	this->setEarthID();
	power_health = H + P;     //not sure 
}

void EarthGunnery::Attack(Unit* unit2)
{

}

int EarthGunnery::getCombination()
{
	return power_health;
}

EarthGunnery::~EarthGunnery()
{
}
