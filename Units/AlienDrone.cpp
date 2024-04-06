#include"AlienDrone.h"

AlienDrone::AlienDrone(int H, int P, int AC, int tj):Unit(H,P,AC,tj)
{
	Type = alienDrone;
}

void AlienDrone::Attack(Unit* unit)
{
}

AlienDrone::~AlienDrone()
{
}
