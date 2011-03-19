#include "humanplayer.hh"

using namespace irr;

HumanPlayer::HumanPlayer(Game *g, irr::core::vector3df pos) : Player(g, pos),
	lastCannon(1) {

	cam = getGame()->getSmgr()->addCameraSceneNode(0, pos, pos + core::vector3df(0,0,1));
	cam->setFarValue(30000.f);
	setNode(cam);
	rotate(core::vector3df(0,180,0));
	setRadius(40);
	velocityMode = false;
	targetVelocity = core::vector3df(0,0,0);
	e = &getGame()->getEventListener();

	power = 200;

}

const irr::core::vector3df HumanPlayer::getRelativeSpeed() {

	core::vector3df up = cam->getUpVector();
	core::vector3df right = up.crossProduct(forward);
	core::vector3df spd = getSpeed();
	core::vector3df relSpeed(spd.dotProduct(right), spd.dotProduct(up),
			spd.dotProduct(forward));
	return relSpeed;
}

void HumanPlayer::hit(int damage) {
	std::cout << "You are hit, hp left: " << getHitPoints() << std::endl;
	getGame()->getSounds()->playDamageSound();
	PhysicalObject::hit(damage);
}

void HumanPlayer::destruct() {
	std::cout << "You are dead, GAME OVER!!" << std::endl;
	getGame()->getDevice()->closeDevice();
}

void HumanPlayer::update(irr::f32 timeStep) {

	power += timeStep*30;
	if (power > 200) power = 200;

	Player::update(timeStep);

}

void HumanPlayer::shoot(const irr::f32 timeStep) {
	if (cooldown <= 0.0 && power >= 20) {
		power -= 10;
		getGame()->getSounds()->playGunSound();
		Laser *p = new Laser(getGame(),
				getPosition() + forward * 10 - cam->getUpVector()*10
				+ lastCannon*15*cam->getUpVector().crossProduct(forward),
				getSpeed() + getGame()->getSettings().PROJECTILE_SPEED * forward);

		p->rotate(getNode()->getRotation());
		getGame()->getProjectiles().push_back(p);
		cooldown = getGame()->getSettings().GUN_COOLDOWN;
		lastCannon *= -1;
	}
}

void HumanPlayer::control(const irr::f32 timeStep) {

	int invert = 1;
	if (getGame()->getSettings().INVERT_PITCH) invert = -1;

    irr::core::matrix4 m;
    m.setRotationDegrees(getNode()->getRotation());

	core::vector3df fwd(0,0,1), fwd_rel(0,0,1);
	core::vector3df up(0,1,0), up_rel(0,1,0);
	core::vector3df right(1,0,0), right_rel(1,0,0);
	
	m.transformVect(fwd);
	m.transformVect(up);
	m.transformVect(right);

	if (e->IsKeyDown(irr::KEY_KEY_V)) {velocityMode = true; targetVelocity = core::vector3df(0,0,0); }
	if (e->IsKeyDown(irr::KEY_KEY_I)) velocityMode = false;

	// ACCELERATION
	//// ACCELERATION
	irr::core::vector3df acc(0, 0, 0), asdf(0,0,0), fasd(0,0,0);

	// accelerate
	if      (e->IsKeyDown(irr::KEY_KEY_W)) {acc += fwd; targetVelocity += fwd_rel;}
	else if (e->IsKeyDown(irr::KEY_KEY_S)) {acc -= fwd; targetVelocity -= fwd_rel;}

	// strafe
	if      (e->IsKeyDown(irr::KEY_KEY_D)) {acc += right; targetVelocity += right_rel;}
	else if (e->IsKeyDown(irr::KEY_KEY_A)) {acc -= right; targetVelocity -= right_rel;}
	// climb
	if      (e->IsKeyDown(irr::KEY_KEY_R)) {acc += up; targetVelocity += up_rel;}
	else if (e->IsKeyDown(irr::KEY_KEY_F)) {acc -= up; targetVelocity -= up_rel;}
	
	//m.transformVect(acc);
	acc.normalize();

	// turbo boost
	if (e->IsKeyDown(irr::KEY_LSHIFT)) acc *= 3;

	// CONTROL MODES
	if (velocityMode) {
		acc = targetVelocity - getRelativeSpeed();
		acc.normalize();
		acc = getNode()->getRotation().rotationToDirection(acc);
	}
	
	accelerate(acc, timeStep);
	//brake
	if (e->IsKeyDown(irr::KEY_SPACE)) accelerate(-getSpeed().normalize(), timeStep);


	// ROTATION
	irr::core::vector3df rot(0, 0, 0);
	irr::core::position2d<irr::f32> mouseDelta = e->getMouseDelta();
	// pitch
	if      (e->IsKeyDown(irr::KEY_UP)) rot += core::vector3df(-invert, 0, 0);
	else if (e->IsKeyDown(irr::KEY_DOWN)) rot += core::vector3df(invert, 0, 0);
	else if (mouseDelta.Y) rot += core::vector3df(-(invert *
				getGame()->getSettings().MOUSE_SENSITIVITY * mouseDelta.Y), 0, 0);
	// yaw
	if      (e->IsKeyDown(irr::KEY_LEFT)) rot += core::vector3df(0,-1, 0);
	else if (e->IsKeyDown(irr::KEY_RIGHT)) rot += core::vector3df(0, 1, 0);
	else if (mouseDelta.X) rot += core::vector3df(0, (-getGame()->getSettings().MOUSE_SENSITIVITY
				* mouseDelta.X), 0);
	// roll
	if      (e->IsKeyDown(irr::KEY_KEY_Q)) rot += core::vector3df(0, 0, 1);
	else if (e->IsKeyDown(irr::KEY_KEY_E)) rot += core::vector3df(0, 0,-1);
	
	// SHOOT
	if (e->IsKeyDown(irr::KEY_CONTROL) || e->IsKeyDown(irr::KEY_LBUTTON)) shoot(timeStep);

	rotate(getGame()->getSettings().TURN_SPEED * timeStep * rot);

	cam->setTarget(getPosition() + fwd);
	cam->setUpVector(up);
	forward = fwd;
	
	if(e->IsKeyDown(irr::KEY_KEY_W) || e->IsKeyDown(irr::KEY_KEY_A) || e->IsKeyDown(irr::KEY_KEY_S) || 
         e->IsKeyDown(irr::KEY_KEY_D) || e->IsKeyDown(irr::KEY_KEY_F) || e->IsKeyDown(irr::KEY_KEY_R)) this->getGame()->getSounds()->playMoveSound(true);
	else this->getGame()->getSounds()->playMoveSound(false);
}

