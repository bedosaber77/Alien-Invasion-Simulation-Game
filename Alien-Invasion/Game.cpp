#include "Game.h"
#include<iostream>
using namespace std;

Game::Game()
{
    pAlienArmy = new AlienArmy;
    pEarthArmy = new EarthArmy;
	pRand = new RandGen;

	StartGame();
}

void Game::StartGame()
{
	//AlienArmy* pAlienArmy = new AlienArmy;
	//EarthArmy* pEarthArmy = new EarthArmy;


	cout << "	ALIEN INVASION ! " << endl
		<< "Please enter your File Parameters path" << endl;
	string Filename;
	cin >> Filename;
	LoadParameters("LoadParameters.txt");
	//MainLoop();
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

		//int ESpercent, ETpercent, EGpercent;// 3 variables?
		Infile >> EarthParameters.ESpercent >> EarthParameters.ETpercent >> EarthParameters.EGpercent;


		//int ASpercent, AMpercent, ADpercent;// 3 variables?
		Infile >> AlienParameters.ASpercent >> AlienParameters.AMpercent >> AlienParameters.ADpercent;


		int Prob;
		Infile >> Prob;


		// here we need to think about another better way(structs)
		Infile >> EarthParameters.lower_power >> EarthParameters.upper_power >>
			EarthParameters.lower_health >> EarthParameters.upper_health >>
			EarthParameters.lower_capacity >> EarthParameters.upper_capacity;

		Infile >> AlienParameters.lower_power >> AlienParameters.upper_power >>
			AlienParameters.lower_health >> AlienParameters.upper_health >>
			AlienParameters.lower_capacity >> AlienParameters.upper_capacity;

		pRand->GenerateUnits( N,  Prob,  EarthParameters,  AlienParameters,TimeStep); //REVISITING + each timestep
		Infile.close();
	}
}


void Game::MainLoop()
{
	 //while (TimeStep != 50 || !CheckWin() || !CheckGameOver())
	/*
	while (TimeStep != 50) //will stop when it completes 50 time steps for now (phase 1)
	{

		TimeStep++;

		// First Generate Units each time step
		//pRand->GenerateUnits(N, Prob, EarthParameters, AlienParameters, TimeStep);


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
	cout << "=========== Earth Army Alive Units ===========" << endl;
	pEarthArmy->Print();
	cout << endl;
	cout << "=========== Alien Army Alive Units ===========" << endl;
	pAlienArmy->Print();
	cout << "=========== Killed/Destructed Units ==========" << endl;
	cout << KilledList.getCount();
	KilledList.print();
}

Game::~Game()
{
	ClearKilledList();
}
