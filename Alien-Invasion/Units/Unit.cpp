#include "Unit.h"
#include"../Game Class/Game.h"

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
	IsHealed = false;
}
//==================================================================================//
//							    Setters/ Getters Functions	         				//
//==================================================================================//
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

int Unit::getTj() const
{
	return Tj;
}

int Unit::getTa() const
{
	return Ta;
}

int Unit::getTd() const
{
	return Td;
}


void Unit::decrementHealth(int damage)
{
	this->Health -= damage;
}

void Unit::incrementHealth(int HealthImp)
{
	//to be made
	this->Health += HealthImp;
}




//==================================================================================//
//							     Heal Unit Functions	       						//
//==================================================================================//
int Unit::getIntialHealth() const
{
	return InitalHealth;
}


/*
    1- Sets time that the units is added to UML
	2- Sets unit into the UML
	3- Sets that this unit is healed-> to not consider it in incrementing health units
*/

void Unit::setTH(int th)
{
	TH = th;
	AddedToUML = true;
}

int Unit::getTH() const
{
	return TH;
}

void Unit::ExitUML()
{
	AddedToUML = false;
	if (!IsHealed)
		pGame->UpdateHealCount();
	IsHealed = true;    //the unit is successfully healed if it exits UML only
}

bool Unit::checkUML() const
{ 
	return AddedToUML;  // checks it is in uml or not, to set its time only once  
}

int Unit::getESPriorty() const
{
	return (InitalHealth - Health);
}


Unit::~Unit()
{
}
// insertion operator overloading
std::ostream& operator<<(std::ostream& os, const Unit* obj)
{
	os << obj->getID();
	return os;
}
