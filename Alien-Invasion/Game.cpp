#include "Game.h"
#include<iostream>
using namespace std;
Game::Game()
{
}

void Game::StartGame()
{
	cout << "	ALIEN INVASION ! " << endl
		<< "Please enter your File Parameters path" << endl;
	string Filename;
	cin >> Filename;
	LoadParameters("LoadParameters.txt");
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
	while (TimeStep++) //will stop when Army Units become zero
	{
		// First Generate Units each time step
		// 
		// 
		// 
		//
		
		//pRand->GenerateUnits(N, Prob, EarthParameters, AlienParameters, TimeStep);
		
		
		
		
		
		//Attack each time step
	}
}

Game::~Game()
{
}
