#ifndef ASTEROIDS_PLANET_HH
#define ASTEROIDS_PLANET_HH

#include "game.hh"
#include "physicalobject.hh"

class Planet : public PhysicalObject {
	public:
		/**
		 * Creates a new projectile
		 * @param position The starting position of the projectile
		 * @param speed The speed vector for the projectile
		 */
		Planet(Game *g, irr::core::vector3df pos, int radius, int mass);
		void update(irr::f32 timeStep); 

	private:

};


#endif
