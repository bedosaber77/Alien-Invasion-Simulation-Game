#include "RandGen.h"
#include"../Units/Unit.h"
#include"../Units/EarthTank.h"
#include"../Units/AlienMonster.h"
#include"../Units/AlienDrone.h"
#include"../Units/EarthGunnery.h"
#include"..\Units\Aliensoldier.h"
RandGen::RandGen(Game* GamePtr)
{
	srand(time(0));
	pGame = GamePtr;

}

Unit* RandGen::GenerateUnits(int ts,ArmyType Army_Type)
{
	
	Unit* newUnit=nullptr;
	
	
		int B = (rand() % 100) + 1;
		//Parameters for Unit Constructor(Earth)

		switch (Army_Type)
		{
		case Earth:
		{
			int ePower = rand() % (EarthParameters.upper_power - EarthParameters.lower_power + 1)
				+ EarthParameters.lower_power;
			int eHealth = rand() % (EarthParameters.upper_health - EarthParameters.lower_health + 1)
				+ EarthParameters.lower_health;
			int eCapacity = rand() % (EarthParameters.upper_capacity - EarthParameters.lower_capacity + 1)
				+ EarthParameters.lower_capacity;

			// Generation of Earth Units


			if (B <= EarthParameters.ESpercent)		//generate ES
			{
				newUnit = new EarthSoldier(eHealth, ePower, eCapacity, ts,pGame);
			}
			else if (B <= EarthParameters.ESpercent + EarthParameters.ETpercent)	//generate ET
			{
				newUnit = new EarthTank(eHealth, ePower, eCapacity, ts, pGame);
			
			}
			else       //generate EG
			{
				newUnit = new EarthGunnery(eHealth, ePower, eCapacity, ts, pGame);

			}
		}
			break;

			//Parameters for Unit Constructor(Alien)

		case Alien:
		

		{
		int aPower = rand() % (AlienParameters.upper_power - AlienParameters.lower_power + 1)
			+ AlienParameters.lower_power;
		int aHealth = rand() % (AlienParameters.upper_health - AlienParameters.lower_health + 1)
			+ AlienParameters.lower_health;
		int aCapacity = rand() % (AlienParameters.upper_capacity - AlienParameters.lower_capacity + 1)
			+ AlienParameters.lower_capacity;


		// Generation of Alien Units

		if (B <= AlienParameters.ASpercent)		//generate AS
		{
			newUnit = new AlienSoldier(aHealth, aPower, aCapacity, ts,pGame);
		}
		else if (B <= AlienParameters.ASpercent + AlienParameters.AMpercent)	//generate AM
		{
			newUnit = new AlienMonster(aHealth, aPower, aCapacity, ts, pGame);
		}
		else       //generate AD
		{
			newUnit = new AlienDrone(aHealth, aPower, aCapacity, ts,pGame);

		}
		}
			break;
		default:
			break;
		}
		
		
	
	return newUnit;
}

void RandGen::SetN(int n)
{
	N = n;
}

void RandGen::SetProb(int Probability)
{
	Prob = Probability;
}

void RandGen::SetEarthParameters(Inputs Eparameters)
{
	EarthParameters = Eparameters;
}

void RandGen::SetAlienParameters(Inputs Aparameters)
{
	AlienParameters = Aparameters;
}

int RandGen::GetN() const
{
	return N;
}

int RandGen::GetProb() const
{
	return Prob;
}


RandGen::~RandGen()
{
}
