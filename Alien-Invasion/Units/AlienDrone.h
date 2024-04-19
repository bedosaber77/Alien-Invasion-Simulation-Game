#include"Unit.h"
class AlienDrone :public Unit
{
public:
	AlienDrone(int H, int P, int AC, int tj);
	virtual void Attack(Unit* unit2); 
	~AlienDrone();

};