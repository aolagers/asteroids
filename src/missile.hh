#ifndef ASTEROIDS_MISSILE_HH
#define ASTEROIDS_MISSILE_HH

#include "projectile.hh"

class Missile : public Projectile {
	public:
		Missile(Game *g, irr::core::vector3df position, irr::core::vector3df velocity);
	private:

};


#endif

