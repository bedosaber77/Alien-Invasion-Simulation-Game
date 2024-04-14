#pragma once
#include<iostream>
#include<string>

enum UnitType {
	earthSoldier, earthTank, earthGunnery,
	alienSoldier, alienMonster, alienDrone
};

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
public:
	Unit(int H,int P,int AC,int tj);
	virtual void Attack(Unit* unit2) = 0;

	//Setters and Getters
	void setHealth(int h);
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
