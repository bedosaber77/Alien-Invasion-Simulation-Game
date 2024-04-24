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

			Print();

			pEarthArmy->Attack();
		//	Print();
			pAlienArmy->Attack();

			Print();
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

void Game::GetEnemiesList(ArmyType Army_Type, UnitType Unit_Type, int Capacity, LinkedQueue<Unit*>& EnemiesList)
{
	Unit* unit2 = nullptr;
	switch (Army_Type)
	{
	case Earth:
	{
		switch (Unit_Type)
		{
		case earthSoldier:
		{
			for (int i = 0; i < Capacity; i++)
			{
				unit2 = pEarthArmy->removeUnit(Unit_Type);

				if (unit2)
				{
					EnemiesList.enqueue(unit2);
				}

			}
		}
		    break;
		}
	}
		break;
	case Alien:
	{
		for (int i = 0; i < Capacity; i++)
		{
			unit2 = pAlienArmy->removeUnit(Unit_Type, i % 2);

			if (unit2)
			{
				EnemiesList.enqueue(unit2);
			}

		}
	}
		break;
	default:
		break;
	}
	return;

}

int Game::GetCurrentTime()
{
	return TimeStep;
}


void Game::PrintKilledList()const
{
	cout << KilledList.getCount() << " units [";
	KilledList.print();
	cout << " ] \n";
}

void Game::Print() const
{
	cout << "Current Timestep " << TimeStep << endl;
	cout << "============== Earth Army Alive Units ==============" << endl;
	pEarthArmy->Print();
	cout << endl;
	cout << "============== Alien Army Alive Units ==============" << endl;
	pAlienArmy->Print();
	cout << endl;
	cout << "============== Killed/Destructed Units ==============" << endl;
	PrintKilledList();

	system("pause");
}

Game::~Game()
{
	ClearKilledList();
	delete pEarthArmy;
	delete pAlienArmy;
	delete pRand;
}

