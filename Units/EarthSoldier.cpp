#include<iostream>
#include<string>
using namespace std;
#include "Earthsoldier.h"

Earthsoldier::Earthsoldier(int H, int P, int AC, int tj):Unit(H,P,AC,tj)
{
	Type = earthSoldier;
}

void Earthsoldier::Attack(Unit* unit2)
{}

Earthsoldier::~Earthsoldier()
{
}
