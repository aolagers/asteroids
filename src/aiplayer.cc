#include "aiplayer.hh"

using namespace irr;

AIPlayer::AIPlayer(Game *g, core::vector3df pos,
		Player *target) : Player(g, pos), target(target) {

	//scene::IMesh* mesh = getGame()->getSmgr()->getMesh(PROJECT_DATA_DIR "/hatak.3ds");	
	scene::IMesh* mesh = getGame()->getSmgr()->getMesh(PROJECT_DATA_DIR "/TIEf3DS8.3ds");	
	scene::ISceneNode* n = getGame()->getSmgr()->addMeshSceneNode(mesh, 0, -1, pos);
//  scene::ISceneNode *n = getGame()->getSmgr()->addSphereSceneNode(10.0f, 16, 0, -1, pos);
	n->setMaterialFlag(video::EMF_LIGHTING, false);
	n->setScale(core::vector3df(5,5,5));

	setNode(n);

	setRadius(30);
	forward = core::vector3df(0,0,1);
}

void AIPlayer::shoot(const irr::f32 timeStep) {
	if (cooldown <= 0.0) {

		Projectile *l = new Laser(getGame(),
				getPosition() + 30*forward,
				getSpeed() + getGame()->getSettings().PROJECTILE_SPEED/5 * forward);

		l->rotate(getNode()->getRotation());

		getGame()->getProjectiles().push_back(l);
		cooldown = getGame()->getSettings().GUN_COOLDOWN * 5;
	}
}

void AIPlayer::control(irr::f32 timeStep) {
	forward = (target->getPosition() - getPosition()).normalize();
	accelerate(0.5*forward, timeStep);

	getNode()->setRotation(forward.getHorizontalAngle());

	if (target != NULL) {
		shoot(timeStep);
	}
}

void AIPlayer::destruct() {
	double distance = (getPosition() - getGame()->getHuman()->getPosition()).getLength();
	getGame()->getSounds()->playExplosionSound(distance);

	Explosion *exp = new Explosion(this);
	getGame()->getExplosions().push_back(exp);

	setRemove(true);
}
