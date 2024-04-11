#pragma once
#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\DS Files\Queue\Deque.h"
#include "..\Units\Unit.h"

class AlienArmy
{
private:
	LinkedQueue <Unit*> AlienSoliders;
	Deque <Unit*> AlienDrones;
	Unit* Monsters[1000];
	int countMonsters;
	static int ID;
public:
	AlienArmy();
	void AddUnit(Unit* newUnit,bool IntoFront=false); //Look at Question 24 in Q&A File
	Unit* removeUnit(UnitType type,bool FromBack=false);
	void Attack();

	//Getters for Lists needed by Attack function
	
	LinkedQueue <Unit*> GetEnemiesList(UnitType type,int Capacity);	//to be revisited

	void Print();
	~AlienArmy();

};

