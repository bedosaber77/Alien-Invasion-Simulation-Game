#include"Unit.h"
class AlienDrone :public Unit
{

public:
	AlienDrone(int H, int P, int AC, int tj, Game* Gameptr);
	virtual bool Attack(Unit* unit2); 
	~AlienDrone();

};