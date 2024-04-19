#include<iostream>
#include<string>
using namespace std;
#include "EarthSoldier.h"

EarthSoldier::EarthSoldier(int H, int P, int AC, int tj):Unit(H,P,AC,tj)
{
	Type = earthSoldier;
}

void EarthSoldier::Attack(Unit* unit2)
{}

EarthSoldier::~EarthSoldier()
{
}
