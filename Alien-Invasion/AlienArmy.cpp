#include "AlienArmy.h"
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\Alien-Invasion\AlienSolider.h"
#include "..\Alien-Invasion\Unit.h"

AlienArmy::AlienArmy()
{
}

void AlienArmy::AddAlienSolider(Unit* AlienUnit)
{
	AlienSoliders.enqueue(AlienUnit);
}

void AlienArmy::DeleteUnit()
{
}

void AlienArmy::Print()
{
}

AlienArmy::~AlienArmy()
{
}
