#include "Game.h"
#include<iostream>
using namespace std;

Game::Game()
{
	srand(time(0));
    pAlienArmy = new AlienArmy;
    pEarthArmy = new EarthArmy;
	pRand = new RandGen(this);

	StartGame();
}

void Game::StartGame()
{
	bool ValidName = false;
	cout << "	ALIEN INVASION ! " << endl
		<< "Please enter your File Parameters path" << endl;
	string Filename;
	while (!ValidName)
	{
		cin >> Filename;
		ValidName = LoadParameters(Filename + ".txt");
	}
	MainLoop();

}

bool Game::LoadParameters(string Filename)
{
	ifstream Infile(Filename);
	if (Infile.is_open())
	{
		Inputs EarthParameters; // instance of struct for Earth Units
		Inputs AlienParameters;  // instance of struct for Army Units


		//Number of units for each army
		int N;
		Infile >> N;
		pRand->SetN(N);


		Infile >> EarthParameters.ESpercent >> EarthParameters.ETpercent >> EarthParameters.EGpercent;
		Infile >> AlienParameters.ASpercent >> AlienParameters.AMpercent >> AlienParameters.ADpercent;

		// Probability
		int Prob;
		Infile >> Prob;
		pRand->SetProb(Prob);



		// Earth Ranges
		Infile >> EarthParameters.lower_power;
		Infile.ignore(1) >> EarthParameters.upper_power;


		Infile >> EarthParameters.lower_health;
		Infile.ignore(1) >> EarthParameters.upper_health;

		Infile >> EarthParameters.lower_capacity;
		Infile.ignore(1) >> EarthParameters.upper_capacity;



		//Alien Ranges
		Infile >> AlienParameters.lower_power;
		Infile.ignore(1) >> AlienParameters.upper_power;


		Infile >> AlienParameters.lower_health;
		Infile.ignore(1) >> AlienParameters.upper_health;

		Infile >> AlienParameters.lower_capacity;
		Infile.ignore(1) >> AlienParameters.upper_capacity;



		//set values for ranges and percentage
		pRand->SetEarthParameters(EarthParameters);
		pRand->SetAlienParameters(AlienParameters);

		Infile.close();
		return true;
	}
	else
	{
		cout << "ERROR, Please enter a valid file name. " << endl;
		return false;

	}
}

void Game::MainLoop()
{
	while (TimeStep <= 50) //will stop when it completes 50 time steps for now (phase 1)
	{
		Unit* newUnit = nullptr;
		int A = (rand() % 100) + 1;
		if (A <= pRand->GetProb())   //Generating Army condition
		{
			// Generating Earth Army
			for (int i = 0; i < pRand->GetN(); i++)
			{
				newUnit = pRand->GenerateUnits(TimeStep, Earth);
				pEarthArmy->AddUnit(newUnit);
			}

			// Generating Alien Army

			for (int i = 0; i < pRand->GetN(); i++)
			{
				newUnit = pRand->GenerateUnits(TimeStep, Alien);
				pAlienArmy->AddUnit(newUnit, i % 2);
			}
		}
		    cout << "============== Units fighting at current step ==============" << endl; 
		    Print();
			//cout << "============== Units fighting at current step ==============" << endl;
			cout << "\033[1;31m============== Killed/Destructed Units ==============" << endl;

			PrintKilledList();
			pEarthArmy->Attack();
			pAlienArmy->Attack();
			cout << "============== Units after attack round ==============" << endl;
			Print();	
			cout << "\n\033[1;31m============== Killed/Destructed Units ==============" << endl;
	        PrintKilledList();
			cout << endl;
	        system("pause");
			TimeStep++;
		}
}
	


void Game::AddtoKilledList(Unit* army)
{
	KilledList.enqueue(army);
}



void Game::ClearKilledList()
{
	Unit* KilledUnit;
	while (!KilledList.isEmpty())
	{
		KilledList.dequeue(KilledUnit);
		delete KilledUnit;
	}

}

void Game::AddtoUML(Unit* unit)
{
	if (unit->getType() == earthSoldier)
		UMLsolider.enqueue(unit, unit->getESPriorty());
	else
		UMLtanks.enqueue(unit);

	bool Healedbefore;
	if (!unit->checkUML(Healedbefore))
	{
		if (!Healedbefore)
			pEarthArmy->incHealedUnits();
		
		unit->setTH(TimeStep);
	}
}

Unit* Game::getUnitToHeal()
{
	Unit* unit=nullptr;
	int pri;
	if (!UMLsolider.isEmpty())
		UMLsolider.dequeue(unit, pri);
	else if (!UMLtanks.isEmpty())
		UMLtanks.dequeue(unit);
	return unit;
}

AlienArmy* Game::GetAlienArmyPtr()
{
	return pAlienArmy;
}

EarthArmy* Game::GetEarthArmyPtr()
{
	return pEarthArmy;
}

RandGen* Game::GetRandGenPtr()
{
	return pRand;
}

Unit* Game::GetEnemiesUnit(ArmyType Army_Type, UnitType Unit_Type,bool BackDrone)
{
	Unit* unit2 = nullptr;
	switch (Army_Type)
	{
	case Earth:
	{
		unit2 = pEarthArmy->removeUnit(Unit_Type);
	}
	break;
	case Alien:
		unit2 = pAlienArmy->removeUnit(Unit_Type, BackDrone % 2);

		break;
	default:
		break;
	}
	return unit2;

}

int Game::GetCurrentTime()
{
	return TimeStep;
}


void Game::PrintKilledList() const
{
	cout << KilledList.getCount() << " units [";
	KilledList.print();
	cout << " ] \n\033[0m";
}

void Game::Print() const
{
	cout << "Current Timestep " << TimeStep << endl;
	cout << "\033[1;36m============== Earth Army Alive Units ==============" << endl;
	pEarthArmy->Print();
	cout << endl;
	cout << "\n\033[1;32m============== Alien Army Alive Units ==============" << endl;
	pAlienArmy->Print();
	cout << endl;
	cout << "\n\033[0m";
}

Game::~Game()
{
	ClearKilledList();
	delete pEarthArmy;
	delete pAlienArmy;
	delete pRand;
}

