#ifndef ASTEROIDS_HUMANPLAYER_HH
#define ASTEROIDS_HUMANPLAYER_HH

#include "player.hh"

class HumanPlayer : public Player {

	public:
		HumanPlayer(Game *g, irr::core::vector3df pos);

		void hit(int damage);

		void control(const irr::f32 timeStep);

		void update(irr::f32 timeStep);

		void shoot(irr::f32 timeStep);

		void destruct();

		const irr::core::vector3df getRelativeSpeed();

		double getPower() { return power; }

		bool getMode() { return velocityMode; }

		irr::scene::ICameraSceneNode* getCam() {return cam;}

	private:

		irr::scene::ICameraSceneNode *cam;

		EventListener *e;

		int lastCannon;

		double power;

		bool velocityMode;

		irr::core::vector3df targetVelocity;
};

#endif
