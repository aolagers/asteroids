#include "planet.hh"

using namespace irr;

Planet::Planet(Game *g, irr::core::vector3df position, int radius, int mass) : PhysicalObject(g) {
	setMass(mass);
	setRadius(radius);

	scene::ISceneNode *n = g->getSmgr()->addSphereSceneNode(radius, 50, 0, -1, position);
	n->setMaterialFlag(video::EMF_LIGHTING, false);
	n->setMaterialTexture(0,
			this->getGame()->getDriver()->getTexture(PROJECT_DATA_DIR "/moon.jpg"));
	setNode(n);
}

//do not move or destruct
void Planet::update(irr::f32 timeStep) {
}
