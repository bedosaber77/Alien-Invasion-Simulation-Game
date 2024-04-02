#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\Units\AlienSolider.h"
#include "..\Units\Unit.h"

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

