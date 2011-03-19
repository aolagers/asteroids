#ifndef ASTEROIDS_ASTEROID_HH
#define ASTEROIDS_ASTEROID_HH

#include "game.hh"
#include "sounds.hh"
#include "explosion.hh"
#include "player.hh"

#include "physicalobject.hh"

/// A dumb physical object that travels through space infinitely.

class Asteroid : public PhysicalObject {
	public:
		/**
		 * Creates a new projectile
		 * @param position The starting position of the projectile
		 * @param speed The speed vector for the projectile
		 */
		Asteroid(Game *g, irr::core::vector3df pos,
				irr::core::vector3df speed, int scale);

		void update(irr::f32 timeStep);

		void destruct();
		
		void setScale(int newScale) { scale = newScale; }
		int getScale() const { return scale; }

	private:
		irr::core::vector3df spin;
		int scale;
};


#endif
