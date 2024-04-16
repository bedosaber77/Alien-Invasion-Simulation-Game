#pragma once
#include<iostream>
#include<string>

//#include"../Alien-Invasion/Game.h"
using namespace std;

#include "..\Alien-Invasion\DEFS.h"
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
	Game* pGame;
public:
	Unit(int H,int P,int AC,int tj,Game* Gameptr);
	virtual void Attack(Unit* unit2=nullptr) = 0;
	void setHealth(int h);
	void setTd(int td);
	void setTa(int ta);

	int getHealth() const;
	int getPower() const;
	int getID() const;
	UnitType getType() const;		
	void setID(int id);

	//Functions to Increment/Decrement health
	void decrementHealth(int damage);
	void incrementHealth(int);		//to be revisited
	~Unit();

};

std::ostream& operator<<(std::ostream& os, const Unit* obj);
