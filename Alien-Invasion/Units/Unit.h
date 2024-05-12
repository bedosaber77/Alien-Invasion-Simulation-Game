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

	//Game pointer
	Game* pGame;

	//Time & Duration Parameters//
	int Tj;		//Join Time
	int Ta;		//First Attacked Time
	int Td;		//Destruction Time

	//Added For Phase 2
	bool GotShot;	// checks if first attack happened or not

	//Heal Unit Parameters
	bool AddedToUML; // checks if it is added to UML or NOT
	int InitalHealth; // Added For Healunit
	int TH;
	bool IsHealed;


public:


	Unit(int H,int P,int AC,int tj,Game* Gameptr);

	//Unit Parameters setters/ getters
	
	int getHealth() const;
	int getPower() const;
	int getID() const;
	UnitType getType() const;		
	void setID(int id);
	void setHealth(int h);

	//Time and Delay setters /getters
	void setTd(int td);
	void setTa(int ta);
	void setTj(int tj);

	int getTj() const;
	int getTa() const;
	int getTd() const;
	

	//Functions to Increment/Decrement health
	void decrementHealth(int damage);
	void incrementHealth(int);		

	//Fighting Function
	virtual void Attack(Unit* unit2 = nullptr) = 0;

	//Heal Unit Functions
	int getIntialHealth() const;
	int getESPriorty() const;
	void setTH(int th);
	int getTH() const;
	bool checkUML() const;
	void ExitUML();
	
	
	
	~Unit();

};

std::ostream& operator<<(std::ostream& os, const Unit* obj);
