#ifndef ASTEROIDS_PROJECTILE_HH
#define ASTEROIDS_PROJECTILE_HH


#include "game.hh"
#include "physicalobject.hh"

/// A dumb physical object that travels through space infinitely.

class Projectile : public PhysicalObject {
	public:
		/**
		 * Creates a new projectile
		 * @param position The starting position of the projectile
		 * @param speed The speed vector for the projectile
		 */
		Projectile(Game *g, irr::core::vector3df position,
				irr::core::vector3df speed);
				
		irr::f32 getLifeTime() { return lifeTime; }

		void hit(int damage);

		void update(irr::f32 timeStep); 

	private:
		irr::f32 lifeTime;
};

#endif
