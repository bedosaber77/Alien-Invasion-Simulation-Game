#pragma once
#include<fstream>
#include<string>
#include"RandGen.h"
#include"Parameters.h"
using namespace std;
class Game
{
	RandGen* pRand;
	int TimeStep=1;
public:
	Game();
	void StartGame();
	void LoadParameters(string);
	void MainLoop();	// Increment time step until game ends
	~Game();
};

