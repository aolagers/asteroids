#ifndef ASTEROIDS_AIPLAYER_HH
#define ASTEROIDS_AIPLAYER_HH

#include "player.hh"

class AIPlayer : public Player {

	public:

		AIPlayer(Game *g, irr::core::vector3df pos, Player *target);

		void control(irr::f32 timeStep);

		void shoot(irr::f32 timeStep);

		void destruct();

	private:

		Player *target;

};

#endif

