#include "Monster.h"
#include <cmath>
Monster::Monster(int H, int P, int AC, int tj):Unit(H,P,AC,tj)
{
	this->setAleinID();
	Type = alienMonster;
}
void Monster::Attack(Unit* unit2)
{
	int damage = (this->getPower() * (this->getHealth() / 100)) / sqrt(unit2->getHealth());
	unit2->setHealth(unit2->getHealth() - damage);
}

Monster::~Monster()
{
}
