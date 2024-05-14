#pragma once
struct Inputs
{

	int lower_power=0, upper_power=0,
		lower_health=0, upper_health=0,
		lower_capacity=0, upper_capacity=0;

	int ESpercent=0, ETpercent=0, EGpercent=0,HUpercent=0;

	int ASpercent=0, AMpercent=0, ADpercent=0;

	int SUpercent=0;
};

enum UnitType {
	earthSoldier, earthTank, earthGunnery,
	alienSoldier, alienMonster, alienDrone,
	healUnit, saverUnit
};

enum ArmyType
{
	Earth, Alien,Ally
};

