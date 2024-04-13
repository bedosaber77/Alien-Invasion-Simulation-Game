#include"AlienDrone.h"
#include"../Alien-Invasion/Game.h"

AlienDrone::AlienDrone(int H, int P, int AC, int tj, Game* Gameptr):Unit(H,P,AC,tj, Gameptr)
{
	Type = alienDrone;
}

void AlienDrone::Attack(Unit* unit2)
{

}

AlienDrone::~AlienDrone()
{
}
