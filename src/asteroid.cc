#include "asteroid.hh"

using namespace irr;

double getRand(double max = 1.0) {
	return (double) max * rand() / RAND_MAX;
}

Asteroid::Asteroid(Game *g, irr::core::vector3df pos,
		irr::core::vector3df speed, int scale) : PhysicalObject(g), scale(scale) {


	scene::IMesh* mesh = getGame()->getSmgr()->getMesh(PROJECT_DATA_DIR "/asteroid2.dae");	
	scene::ISceneNode* n = getGame()->getSmgr()->addMeshSceneNode(mesh, 0, -1, pos);

	n->setMaterialTexture(0, getGame()->getDriver()->getTexture(PROJECT_DATA_DIR "/marsclouds2.jpg"));

//	scene::ISceneNode* n = getGame()->getSmgr()->addCubeSceneNode(10.0f, 0, -1, pos);
	n->setScale(core::vector3df(0.7*scale, 0.7*scale, 0.7*scale));

	n->setMaterialFlag(video::EMF_LIGHTING, false);

	setNode(n);

	spin = core::vector3df(getRand(), getRand(), getRand());

	setSpeed(speed);

	setMass(scale * 10000);
	setRadius(scale * 25.0);
	setHitPoints(scale * 50);
}

void Asteroid::update(irr::f32 timeStep) {
	setPosition(getPosition() + getSpeed() * timeStep);
	rotate(spin);
}

void Asteroid::destruct() {

	--scale;

	Explosion *exp = new Explosion(this);
	getGame()->getExplosions().push_back(exp);

	core::vector3df rnd(getRand(360),getRand(360), getRand(360));
	core::vector3df spd = getSpeed();
	spd = rnd.rotationToDirection(spd);

	if (scale > 0) {
		getGame()->getAsteroids().push_back(new Asteroid(getGame(), getPosition(), spd * getRand(1.5), scale));
		getGame()->getAsteroids().push_back(new Asteroid(getGame(), getPosition(), -spd * getRand(1.5), scale));
	}

	double distance = (getPosition() - getGame()->getHuman()->getPosition()).getLength();
	getGame()->getSounds()->playExplosionSound(distance);

	PhysicalObject::destruct();

}
