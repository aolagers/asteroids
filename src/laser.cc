#include "laser.hh"

using namespace irr;

Laser::Laser(Game *g, irr::core::vector3df position, irr::core::vector3df velocity) :
	Projectile(g, position, velocity) {

	scene::ISceneNode *n;
	n = getGame()->getSmgr()->addCubeSceneNode(10.0f, 0, -1, position);
	n->setMaterialFlag(video::EMF_LIGHTING, false);
	n->setScale(core::vector3df(0.5, 0.5, 5));
	n->setMaterialTexture(0, getGame()->getDriver()->getTexture(PROJECT_DATA_DIR"/laser.png"));
	setNode(n);
	setHitPoints(1);

}

