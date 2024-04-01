#pragma once
#include<iostream>
#include<string>
using namespace std;
class Unit
{
protected:
	int ID;
	string Type;
	int Health;
	int Power;
	int Attack_Capacity;
	//Time & Duration Parameters//
	int Tj;		//Join Time
	int Ta;		// First Attacked Time
	int Td;		//Destruction Delay
public:
	Unit();
	virtual void Attack() = 0;
	~Unit();

};

