#ifndef ASTEROIDS_LASER_HH
#define ASTEROIDS_LASER_HH

#include "projectile.hh"

class Laser : public Projectile {
	public:
		Laser(Game *g, irr::core::vector3df position, irr::core::vector3df velocity);
	private:
};

#endif

