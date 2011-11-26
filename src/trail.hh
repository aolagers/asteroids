#ifndef ASTEROIDS_TRAIL_HH
#define ASTEROIDS_TRAIL_HH

#include "game.hh"

#include "physicalobject.hh"

class Trail : public PhysicalObject {
	public:

		Trail(Game *g, irr::core::vector3df pos);

		void update(irr::f32 timeStep);

		int getLifeTime() { return lifeTime; }

	private:
		irr::f32 lifeTime;

};

#endif
