#include "physicalobject.hh"

using namespace irr;

PhysicalObject::PhysicalObject(Game *g) : g(g),
	radius(0), mass(0), hitPoints(0), remove(false) {

	speed = core::vector3df(0, 0, 0);
}


void PhysicalObject::accelerate(irr::core::vector3df direction, irr::f32 timeStep) {
	speed += (getGame()->getSettings().ACCELERATION_SPEED) * timeStep * direction;
}

void PhysicalObject::update(irr::f32 timeStep) {
	setPosition(getPosition() + getSpeed() * timeStep);
}

void PhysicalObject::rotate(irr::core::vector3df rot) {
	irr::core::matrix4 m;
	m.setRotationDegrees(getNode()->getRotation());
	irr::core::matrix4 n;
	n.setRotationDegrees(rot);
	m *= n;
	getNode()->setRotation( m.getRotationDegrees() );
}

bool PhysicalObject::intersectsWith(PhysicalObject &other) {

	irr::f32 distance = (getPosition() - other.getPosition()).getLength();

	if (distance < (radius + other.getRadius()))
		return true;

	return false;
}

void PhysicalObject::hit(int damage) {
	hitPoints -= damage;
	if (hitPoints <= 0)
		destruct();
}

void PhysicalObject::destruct() {
	setRemove(true);
}

