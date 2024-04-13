#include<iostream>
#include<string>
using namespace std;
#include "EarthSolider.h"

EarthSolider::EarthSolider(int H, int P, int AC, int tj):Unit(H,P,AC,tj)
{
	Type = earthSoldier;
}

void EarthSolider::Attack(Unit* unit2)
{}

EarthSolider::~EarthSolider()
{
}
