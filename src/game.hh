#ifndef ASTEROIDS_GAME_HH
#define ASTEROIDS_GAME_HH

#include <irrlicht.h>
#include <iostream>
//#include <string>
//#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>

#include "config.h"
#include "settings.hh"
#include "eventlistener.hh"
//#include "hud.hh"

class Asteroid;
class PhysicalObject;
class Projectile;
class Player;
class Hud;
class Explosion;
class Sounds;

class DeviceWrapper {
	public:

		DeviceWrapper() : dev(NULL) {};
		~DeviceWrapper() { if (dev) dev->drop(); }

		void init(EventListener *e) {
			dev = irr::createDevice(irr::video::EDT_OPENGL,
					irr::core::dimension2d<irr::u32>(1280, 800), 32,
					false, false, false, e);
		}

		irr::IrrlichtDevice* get() { return dev; }

	private:
		irr::IrrlichtDevice* dev;
};


/// Controls the game world
class Game {

	public:

		Game(const char*);

		~Game();


		void run();

		irr::scene::ISceneManager* getSmgr() { return smgr; }
		irr::ITimer* getTimer() { return timer; }
		irr::IrrlichtDevice *getDevice() { return device.get(); }
		irr::video::IVideoDriver* getDriver() { return driver; }
		Sounds* getSounds() { return snd; }
		Hud* getHud() { return hud; }
		EventListener& getEventListener() { return e; }
		Player* getHuman() { return human; }
		Settings& getSettings() { return settings; }

		boost::ptr_vector<Asteroid>& getAsteroids() { return asteroids; }
		boost::ptr_vector<Projectile>& getProjectiles() { return projectiles; }
		boost::ptr_vector<Player>& getPlayers() { return players; }
		boost::ptr_vector<PhysicalObject>& getObjects() { return objects; }
		boost::ptr_vector<Explosion>& getExplosions() { return explosions; }
		
		void setHud(Hud* h) { hud = h; }
		void setHuman(Player* p) { human = p; }
		void setSettings(Settings set) { settings = set; }
		
	private:
	
		void applyGravitation(irr::f32 timeStep);
		void updateObjects(irr::f32 timeStep);
		void checkCollisions();
		
		Settings settings;
		
		DeviceWrapper device;
		irr::video::IVideoDriver *driver;
		irr::scene::ISceneManager *smgr;
		irr::ITimer *timer;

		EventListener e;
		Sounds *snd;
		Hud *hud;
		
		Player* human;
		
		boost::ptr_vector<PhysicalObject> objects;
		boost::ptr_vector<Player> players;
		boost::ptr_vector<Asteroid> asteroids;
		boost::ptr_vector<Projectile> projectiles;
		boost::ptr_vector<Explosion> explosions;

//		std::vector<Asteroid> a;

};

#endif
