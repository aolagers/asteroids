#include "projectile.hh"

using namespace irr;

Projectile::Projectile(Game *g, irr::core::vector3df position,
		irr::core::vector3df spd) : PhysicalObject(g), lifeTime(0) {
	//setNode(getGame()->getSmgr()->addSphereSceneNode(10.0f, 16, 0, -1, pos));
	setSpeed(spd);
}

void Projectile::hit(int) {
	destruct();
	//setRemove(true);
}

void Projectile::update(irr::f32 timeStep) {
	setPosition(getPosition() + getSpeed() * timeStep);
	lifeTime += timeStep;
	//std::cout << lifeTime << std::endl;
}
