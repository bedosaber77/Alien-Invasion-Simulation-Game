#include"Unit.h"
class AlienDrone :public Unit
{
public:
	AlienDrone(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2); //	thinking about Attack call
	~AlienDrone();

};