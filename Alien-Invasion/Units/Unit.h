#pragma once
#include<iostream>
#include<string>
using namespace std;
#include "..\DEFS.h"
#include "..\DS Files\Queue\LinkedQueue.h"
class Game;				//forward declaration

class Unit
{
protected:
	//Unit Main Parameters
	
	int ID; 
	UnitType Type; 
	int Health;
	int Power;
	int Attack_Capacity;
	//Time & Duration Parameters//
	int Tj;		//Join Time
	int Ta;		//First Attacked Time
	int Td;		//Destruction Delay
	//Added For Phase 2
	bool GotShot;	// checks if first attack happened or not
	bool AddedToUML; // checks if it is added to UML or NOT
	Game* pGame;
	int InitalHealth; // Added For Healunit
	int TH;
public:
	Unit(int H,int P,int AC,int tj,Game* Gameptr);
	virtual void Attack(Unit* unit2 = nullptr) = 0;
	void setHealth(int h);
	void setTd(int td);
	void setTa(int ta);
	void setTj(int tj);

	int getHealth() const;
	int getPower() const;
	int getID() const;
	UnitType getType() const;		
	void setID(int id);
	
	//Functions to Increment/Decrement health
	void decrementHealth(int damage);
	void incrementHealth(int);		//to be revisited
	//For Heal

	int getIntialHealth() const;
	int getESPriorty() const;
	void setTH(int th);
	int getTH() const;
	bool checkUML() const;
	void ExitUML();

	//Print current fight function
	virtual void PrintFight(LinkedQueue<Unit*> EnemiesList)= 0;
	~Unit();

};

std::ostream& operator<<(std::ostream& os, const Unit* obj);
