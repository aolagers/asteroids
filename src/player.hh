#ifndef ASTEROIDS_PLAYER_HH
#define ASTEROIDS_PLAYER_HH

#include "game.hh"
#include "laser.hh"
#include "explosion.hh"
#include "sounds.hh"

/// A keyboard-controllable player with a camera attached to it.

class Player : public PhysicalObject {

	public:

		Player(Game *g, irr::core::vector3df pos);

		virtual void update(const irr::f32 timeStep);

		virtual void control(const irr::f32 timeStep) = 0;

		void destruct();

		irr::core::vector3df getForward() { return forward; }

		irr::core::vector3df forward;
		irr::f32 cooldown;

	private:

};

#endif
