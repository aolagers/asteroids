#ifndef ASTEROIDS_EXPLOSION_HH
#define ASTEROIDS_EXPLOSION_HH

#include "game.hh"
#include "physicalobject.hh"

class Explosion : public PhysicalObject {
	public:

		Explosion(PhysicalObject *target);

		void update(irr::f32 timeStep);
		
		int getLifeTime() { return lifeTime; }

	private:
        irr::f32 lifeTime;
};


#endif
