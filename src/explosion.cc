#include "explosion.hh"

using namespace irr;

Explosion::Explosion(PhysicalObject *target) : PhysicalObject(target->getGame()), lifeTime(0) {

	// create a particle system

	scene::IParticleSystemSceneNode* ps =
		getGame()->getSmgr()->addParticleSystemSceneNode(false);

	scene::IParticleEmitter* em = ps->createSphereEmitter(
			target->getPosition(), // emitter size
			30,   //radius
			core::vector3df(0.0f,0.0f,0.0f),// initial direction
			60,80,                             // emit rate
			video::SColor(0,255,255,255),       // darkest color
			video::SColor(0,255,255,255),       // brightest color
			800,2000,0,                         // min and max age, angle
			core::dimension2df(10.f,10.f),         // min size
			core::dimension2df(20.f,20.f));      // max size

	ps->setEmitter(em); // this grabs the emitter
	em->drop(); // so we can drop it here without deleting it

	scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

	ps->addAffector(paf); // same goes for the affector
	paf->drop();

	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, getGame()->getDriver()->getTexture(PROJECT_DATA_DIR "/fire.bmp"));
	ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

	setNode(ps);

//	setSpeed(core::vector3df(0,0,0));

}

void Explosion::update(irr::f32 timeStep) {
	lifeTime += timeStep;

	//setPosition(getPosition() + 0.3*getSpeed() * timeStep);
	
	if(lifeTime > 0.7)
		setRemove(true);
}


