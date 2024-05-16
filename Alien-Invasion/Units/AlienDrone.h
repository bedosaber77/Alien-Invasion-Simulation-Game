#include"Unit.h"
class AlienDrone :public Unit
{

public:
	AlienDrone(double H, double P, int AC, int tj, Game* Gameptr);
	virtual void Attack();
	~AlienDrone();

};