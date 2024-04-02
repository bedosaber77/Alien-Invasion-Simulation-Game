#include "AlienArmy.h"
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\Units\AlienSolider.h"
#include "..\Units\Unit.h"

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
