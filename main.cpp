#include "DS Files/Queue/Deque.h"
#include "DS Files/Queue/LinkedQueue.h"
#include "../Alien-Invasion-Simulation-Game/Units/EarthSolider.h"
#include "DS Files/Priority Queue/priQueue.h"

int main() { 
	priQueue<Unit*> d;
	LinkedQueue<Unit*> j;
	for (int i = 0; i < 5; i++)
	{
	Unit* ptr = new EarthSolider(15, 15, 15, 15);
	d.enqueue(ptr,i);
	}
	//d.print();
};