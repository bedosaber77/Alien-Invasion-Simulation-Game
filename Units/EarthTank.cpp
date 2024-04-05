#include "EarthTank.h"
#include <cmath>
EarthTank::EarthTank(int H, int P, int AC, int tj) :Unit(H, P, AC, tj)
{
	this->setEarthID();
	Type = earthTank;
}
void EarthTank::Attack(Unit* unit2)
{
	int damage = (this->getPower() * (this->getHealth() / 100)) / sqrt(unit2->getHealth());
	unit2->setHealth(unit2->getHealth() - damage);
}

EarthTank::~EarthTank()
{
}
