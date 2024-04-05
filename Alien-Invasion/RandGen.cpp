#include "RandGen.h"
#include"../Units/Unit.h"
#include"../Units/EarthTank.h"
#include"../Units/Monster.h"
#include"../Units/AlienDrone.h"
#include"..\Units\AlienSolider.h"
#include<time.h>

RandGen::RandGen()
{
	pEarthArmy = new EarthArmy;
}

void RandGen::GenerateUnits(int N, int Prob, Inputs EarthParameters, Inputs AlienParameters,int ts)
{
	srand(time(0));
	int A = (rand() % 100) + 1;
	//Main 2 Loops 
	if (A <= Prob)
	{
		//Parameters for Unit Constructor(Earth)
		while (N--)
		{
			int B = (rand() % 100) + 1;

			int ePower = rand() % (EarthParameters.upper_power - EarthParameters.lower_power + 1)
				+ EarthParameters.lower_power;
			int eHealth = rand() % (EarthParameters.upper_health - EarthParameters.lower_health + 1)
				+ EarthParameters.lower_health;
			int eCapacity = rand() % (EarthParameters.upper_capacity - EarthParameters.lower_capacity + 1)
				+ EarthParameters.lower_capacity;

			// Generation of Earth Units

			Unit* newUnit;
			//pEarthArmy = new EarthArmy();	//will be removed
			if (B <= EarthParameters.ESpercent)		//generate ES
			{
				newUnit = new EarthSolider(eHealth, ePower, eCapacity, ts); //لامؤاخذاه يا مدحت يا اخويا 
				pEarthArmy->AddUnit(newUnit, 1);	//replace with Type name
			}
			else if (B <= EarthParameters.ESpercent + EarthParameters.ETpercent)	//generate ET
			{
				newUnit = new EarthTank(eHealth, ePower, eCapacity, ts);
				pEarthArmy->AddUnit(newUnit, 2);
			}
			else       //generate EG
			{
				//pEarthArmy->AddUnit(newUnit, 3);

			}
			
		}



		//Parameters for Unit Constructor(Alien)
		while (N--)
		{
			int B = (rand() % 100) + 1;

			int aPower = rand() % (AlienParameters.upper_power - AlienParameters.lower_power + 1)
				+ AlienParameters.lower_power;
			int aHealth = rand() % (AlienParameters.upper_health - AlienParameters.lower_health + 1)
				+ AlienParameters.lower_health;
			int aCapacity = rand() % (AlienParameters.upper_capacity - AlienParameters.lower_capacity + 1)
				+ AlienParameters.lower_capacity;


			// Generation of aUnits
			Unit* newUnit;

			if (B <= AlienParameters.ASpercent)		//generate AS
			{
				newUnit = new AlienSolider(aHealth, aPower, aCapacity,ts );
			}
			else if (B <= AlienParameters.ASpercent + AlienParameters.AMpercent)	//generate AM
			{
				newUnit = new Monster(aHealth, aPower, aCapacity, ts );

			}
			else       //generate AD
			{
				newUnit = new AlienDrone(aHealth, aPower, aCapacity,ts );

			}
		}
	}
	else {
		GenerateUnits( N,  Prob,  EarthParameters,  AlienParameters,  ts); //should be removed? -tasneem
	}
}


RandGen::~RandGen()
{
}
