#include"Unit.h"
class AlienDrone :public Unit
{
private:
//	LinkedQueue<Unit*> EnemiesList;
public:
	AlienDrone(int H, int P, int AC, int tj, Game* Gameptr);
	virtual void Attack(Unit* unit2); 
	virtual void PrintFight(LinkedQueue<int> EnemiesList);
	~AlienDrone();

};