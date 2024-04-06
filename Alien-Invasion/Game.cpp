#include "Game.h"
#include<iostream>
using namespace std;

Game::Game()
{
	srand(time(0));
    pAlienArmy = new AlienArmy;
    pEarthArmy = new EarthArmy;
	pRand = new RandGen;

	StartGame();
}

void Game::StartGame()
{

	cout << "	ALIEN INVASION ! " << endl
		<< "Please enter your File Parameters path" << endl;
	string Filename;
	cin >> Filename;
	LoadParameters( Filename+".txt");
}

void Game::LoadParameters(string Filename)
{
	ifstream Infile(Filename);
	if (Infile.is_open())
	{
		Inputs EarthParameters;
		Inputs AlienParameters;
	

		int N;	//Number of units for each army
		Infile >> N;
		pRand->SetN(N);

		
		Infile >> EarthParameters.ESpercent >> EarthParameters.ETpercent >> EarthParameters.EGpercent;


		Infile >> AlienParameters.ASpercent >> AlienParameters.AMpercent >> AlienParameters.ADpercent;


		int Prob;
		Infile >> Prob;


		pRand->SetProb(Prob);
		
		// here we need to think about another better way(structs)


		// Earth Ranges
		Infile >> EarthParameters.lower_power;
		Infile.ignore(1);
		Infile >> EarthParameters.upper_power >>
			EarthParameters.lower_health;
		Infile.ignore(1) >> EarthParameters.upper_health >>
			EarthParameters.lower_capacity;
		Infile.ignore(1) >> EarthParameters.upper_capacity;



		//Alien Ranges

		Infile >> AlienParameters.lower_power;
		Infile.ignore(1);
		Infile >> AlienParameters.upper_power >>
			AlienParameters.lower_health;
		Infile.ignore(1) >> AlienParameters.upper_health >>
			AlienParameters.lower_capacity;
		Infile.ignore(1) >>  AlienParameters.upper_capacity;



		//set
		pRand->SetEarthParameters(EarthParameters);
		pRand->SetAlienParameters(AlienParameters);

		Infile.close();
	}
	MainLoop();
}


void Game::MainLoop()
{
	 //while (TimeStep != 50 || !CheckWin() || !CheckGameOver())
	/*
	while (TimeStep != 50) //will stop when it completes 50 time steps for now (phase 1)
	{

		TimeStep++;

		// First Generate Units each time step
		//pRand->GenerateUnits(TimeStep);

		//should be in print function
		/*
		//Press any key to move to the next timestep
		cout << "Press any key to move to the next timestep" << endl;
		system("pause");
		print();
		*/
		//Attack each time step
	//}
	//}
	while (TimeStep != 50) //will stop when it completes 50 time steps for now (phase 1)
	{
		Unit* newUnit = nullptr;
		int A = (rand() % 100) + 1;
		if (A <= pRand->GetProb())// Generating Army condition
		{	
		for (int i = 0; i < pRand->GetN(); i++)
	    {
				newUnit = pRand->GenerateUnits(TimeStep, Earth);
				pEarthArmy->AddUnit(newUnit);
		}

		// Generating Alien Army

		for (int i = 0; i < pRand->GetN(); i++)
		{
			newUnit = pRand->GenerateUnits(TimeStep, Alien);
			pAlienArmy->AddUnit(newUnit);
		}
	    }
		Print();
		TimeStep++;
	}
	
}

void Game::AddtoKilledList(Unit* army)
{
	KilledList.enqueue(army);
}

void Game::AddtoTempList(Unit* army)
{
	TempList.enqueue(army);
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


void Game::Print()
{
	cout << "Current Timestep " << TimeStep << endl;
	cout << "============== Earth Army Alive Units ==============" << endl;
	pEarthArmy->Print();
	cout << endl;
	cout << "============== Alien Army Alive Units ==============" << endl;
	pAlienArmy->Print();
	cout << endl;
	cout << "============== Killed/Destructed Units ==============" << endl;
	cout << KilledList.getCount();
	KilledList.print();
	cout << endl;
	char a;
	cout << "Enter any Key To Continue\n";
	cin >> a;
	cin.ignore();
}

Game::~Game()
{
	ClearKilledList();
}
