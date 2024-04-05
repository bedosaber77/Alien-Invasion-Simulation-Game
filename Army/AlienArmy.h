#include "..\DS Files\Queue\LinkedQueue.h"
#include "..\DS Files\Queue\Deque.h"
#include "..\Units\Unit.h"

class AlienArmy
{
private:
	LinkedQueue <Unit*> AlienSoliders;
	Deque <Unit*> AlienDrones;
	Unit* Monsters[1000];
	int countMonsters;
public:
	AlienArmy();
	void AddUnit(Unit* newUnit);
	Unit* removeUnit(UnitType type);
	void Attack();
	void Print();
	~AlienArmy();

};

