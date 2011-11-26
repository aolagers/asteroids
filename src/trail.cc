#include "trail.hh"

using namespace irr;

Trail::Trail(Game *g, irr::core::vector3df pos) : PhysicalObject(g) {

	//scene::IMesh* mesh = getGame()->getSmgr()->getMesh(PROJECT_DATA_DIR "/asteroid2.dae");	
	//scene::ISceneNode* n = getGame()->getSmgr()->addMeshSceneNode(mesh, 0, -1, pos);
	//
	scene::ISceneNode *n = g->getSmgr()->addSphereSceneNode(5, 50, 0, -1, pos);
	n->setMaterialFlag(video::EMF_LIGHTING, false);

	//n->setMaterialTexture(0, getGame()->getDriver()->getTexture(PROJECT_DATA_DIR "/marsclouds2.jpg"));

	//n->setScale(core::vector3df(0.7, 0.7, 0.7));
	//n->setMaterialFlag(video::EMF_LIGHTING, false);

	setNode(n);

	setHitPoints(100);
}

void Trail::update(irr::f32 timeStep) {
	lifeTime += timeStep;
	if (lifeTime > 5.0)
		setRemove(true);
}

