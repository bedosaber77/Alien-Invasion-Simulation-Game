#pragma once
#include<iostream>
#include<string>
using namespace std;

enum UnitType {
	earthSoliders, earthTank, earthGunnery,
	alienSolider, alienMonster, alienDrone
};

class Unit
{
protected:
	int ID; // making ID Static Needed To be Revisit??
	static int AlienID;
	static int EarthID;
	UnitType Type; //still thinking >> ?
	int Health;
	int Power;
	int Attack_Capacity;
	//Time & Duration Parameters//
	int Tj;		//Join Time
	int Ta;		// First Attacked Time
	int Td;		//Destruction Delay
public:
	Unit(int H,int P,int AC,int tj);
	virtual void Attack(Unit* unit2) = 0;
	void setHealth(int h);
	int getHealth();
	int getPower();
	int getID();
	UnitType getType();		//to be revisit
	void setAleinID();
	void setEarthID();
	//More Functions Needed
	void decrementHealth(int damage);
	void incrementHealth(int);		//to be revisited
	friend std::ostream& operator<<(std::ostream& os, const Unit* obj);

	~Unit();

};

