#pragma once
#include<iostream>
#include<string>
//#include"../Alien-Invasion/Game.h"
using namespace std;
class Game;				//forward declaration
enum UnitType {
	earthSoliders, earthTank, earthGunnery,
	alienSolider, alienMonster, alienDrone
};

class Unit
{
protected:
	int ID; // making ID Static Needed To be Revisit??
	UnitType Type; //still thinking >> ?
	int Health;
	int Power;
	int Attack_Capacity;
	//Time & Duration Parameters//
	int Tj;		//Join Time
	int Ta;		// First Attacked Time
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

	int getHealth();
	int getPower();
	int getID() const;
	UnitType getType();		//to be revisit
	void setID(int id);
	//More Functions Needed
	void decrementHealth(int damage);
	void incrementHealth(int);		//to be revisited
	friend std::ostream& operator<<(std::ostream& os, const Unit* obj);

	~Unit();

};

