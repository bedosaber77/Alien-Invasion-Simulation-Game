#include "Unit.h"
#include"../Game Class/Game.h"

Unit::Unit(double H, double P, int AC, int tj, Game* Gameptr)
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
	IsInfected = false;
}
//==================================================================================//
//							    Setters/ Getters Functions	         				//
//==================================================================================//
void Unit::setHealth(double h)
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

double Unit::getHealth() const
{
	return this->Health;
}

double Unit::getPower() const
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


void Unit::decrementHealth(double damage)
{
	this->Health -= damage;
}

void Unit::incrementHealth(double HealthImp)
{
	//to be made
	this->Health += HealthImp;
}




//==================================================================================//
//							     Heal Unit Functions	       						//
//==================================================================================//
double Unit::getIntialHealth() const
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
// Infection Setters/ Getters
void   Unit:: SetInfected(bool infected)
{
	IsInfected = infected;
}
bool Unit::InfectedBefore() const
{
	return IsInfected;
}

void Unit::SetImmuned(bool immuned)
{
	IsImmuned = immuned;
}
bool Unit::ImmunedBefore() const
{
	return IsImmuned;
}
Unit::~Unit()
{
}
// insertion operator overloading
std::ostream& operator<<(std::ostream& os, const Unit* obj)
{
	if(obj->InfectedBefore())
	{
		os << '*';
	}
	os << obj->getID();
	return os;
}
