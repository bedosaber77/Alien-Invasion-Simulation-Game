#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\Alien-Invasion\AlienSolider.h"
#include "..\Alien-Invasion\Unit.h"

class AlienArmy
{
private:
	LinkedQueue <Unit*> AlienSoliders;
public:
	AlienArmy();
	void AddAlienSolider(Unit* AlienUnit);
	void DeleteUnit();
	void Print();
	~AlienArmy();

};

