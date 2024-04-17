#include "AlienDrone.h"

AlienDrone::AlienDrone(int p, int h, int c, int timestep) : Units(alienDrone, p, h, c, timestep)
{
	id = aID;
}

bool AlienDrone::Attack()
{
	return true;
}

bool AlienDrone::GetAttacked()
{
	return true;
}

bool AlienDrone::IsDead()
{
	return true;

}
