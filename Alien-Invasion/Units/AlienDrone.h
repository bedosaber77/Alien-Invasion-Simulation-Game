#include"Unit.h"
class AlienDrone :public Unit
{
private:
//	LinkedQueue<Unit*> EnemiesList;
public:
	AlienDrone(int H, int P, int AC, int tj, Game* Gameptr);
	virtual bool Attack(Unit* unit2); 
	~AlienDrone();

};