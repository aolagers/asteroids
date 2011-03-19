#include "player.hh"

using namespace irr;

Player::Player(Game *g, core::vector3df pos) : PhysicalObject(g), cooldown(0) {

	setHitPoints(200);
}

void Player::destruct() {

	double distance = (getPosition() - getGame()->getHuman()->getPosition()).getLength();
	getGame()->getSounds()->playExplosionSound(distance);

	PhysicalObject::destruct();

}

void Player::update(const irr::f32 timeStep) {
	setPosition(getPosition() + getSpeed() * timeStep);
	cooldown -= timeStep;
	control(timeStep);
}

