#include "Unit.h"

Unit::Unit(int H, int P, int AC, int tj, Game* Gameptr)
{
	Health = H;
	Power = P;
	Attack_Capacity = AC;
	Tj = tj;
	ID = 0;
	//Added For Phase 2	
	GotShot = false;
	pGame = Gameptr;
	
	InitalHealth = H;
}

void Unit::setHealth(int h)
{
	this->Health = h;
}

void Unit::setTd(int td)
{
	Td = td;
}

void Unit::setTa(int ta)
{
	if (!GotShot)
	{
		Ta = ta;
		GotShot = true;
	}
}

void Unit::setTj(int tj)
{
	Tj = tj;
}

int Unit::getHealth() const
{
	return this->Health;
}

int Unit::getPower() const
{
	return this->Power;
}
int Unit::getID() const
{
	return this->ID;
}

 UnitType Unit::getType() const
{
	return this->Type;
}

void Unit::setID(int id)
{
	this->ID = id;
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


std::ostream& operator<<(std::ostream& os, const Unit* obj)
{
	os << obj->getID();
	return os;
}
