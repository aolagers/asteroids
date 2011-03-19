#include "missile.hh"

using namespace irr;

Missile::Missile(Game *g, irr::core::vector3df position,
		irr::core::vector3df velocity) : Projectile(g, position, velocity) {

}
