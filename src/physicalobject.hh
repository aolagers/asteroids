#ifndef ASTEROIDS_PHYSICALOBJECT_HH
#define ASTEROIDS_PHYSICALOBJECT_HH

#include "game.hh"
#include <boost/utility.hpp>

class NodeWrapper {
	public:
		NodeWrapper() : node(NULL) {};
		~NodeWrapper() { if (node) node->remove(); }
		void set(irr::scene::ISceneNode *n) { node = n; }
		irr::scene::ISceneNode* get() { return node; }
	private:
		irr::scene::ISceneNode *node;
};

class PhysicalObject : boost::noncopyable {
	public:
		
		PhysicalObject(Game *g);

		irr::scene::ISceneNode *getNode() { return node.get(); }
		Game *getGame() { return g; }
		irr::f32 getMass() { return mass; }
		irr::f32 getRadius() { return radius; }
		irr::core::vector3df getSpeed() { return speed; }
		irr::core::vector3df getPosition() { return getNode()->getPosition(); }
		bool getRemove() {return remove;}
		int getHitPoints() { return hitPoints; }
		
		void setPosition(irr::core::vector3df vec) { getNode()->setPosition(vec); }
		void setSpeed(irr::core::vector3df newSpeed) { speed = newSpeed; }
		void setMass(irr::f32 newmass) { mass = newmass; } 
		void setRadius(irr::f32 newradius) { radius = newradius; }
		void setNode(irr::scene::ISceneNode *n) { node.set(n); }
		void setRemove(bool b) { this->remove = b; }
		void setHitPoints(int hp) { hitPoints = hp; }


		void accelerate(irr::core::vector3df direction, irr::f32 timeStep);
		void rotate(irr::core::vector3df rot);

		virtual void update(irr::f32 timeStep); 

		bool intersectsWith(PhysicalObject &other);

		virtual void hit(int damage);
		virtual void destruct();

	private:

		Game *g;
		NodeWrapper node;

		irr::core::vector3df speed;
		irr::f32 mass;
		irr::f32 radius;

		int hitPoints;
		bool remove;
};

#endif
