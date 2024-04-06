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

int Unit::getID()
{
	return ID;
}

UnitType Unit::getType()
{
	return this->Type;
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

void Unit::decrementHealth(int damage)
{
	this->Health -= damage;
}

void Unit::incrementHealth(int)
{
	//to be made
}

Unit::~Unit()
{
}

int Unit::EarthID = 1;
int Unit::AlienID = 2000;

std::ostream& operator<<(std::ostream& os, const Unit* obj)
{
	os << obj->ID;
	return os;
}
