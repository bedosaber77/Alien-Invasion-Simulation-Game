#include "Unit.h"

Unit::Unit(int H, int P, int AC, int tj)
{
	Health = H;
	Power = P;
	Attack_Capacity = AC;
	Tj = tj;
}

void Unit::setHealth(int h)
{
	this->Health = h;
}

int Unit::getHealth()
{
	return this->Health;
}

int Unit::getPower()
{
	return this->Power;
}

void Unit::setAleinID()
{
	ID = AlienID;
	AlienID++;
}

void Unit::setEarthID()
{
	ID = EarthID;
	EarthID++;
}

Unit::~Unit()
{
}

int Unit::EarthID = 1;
int Unit::AlienID = 2000;