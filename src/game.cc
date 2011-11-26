#include <algorithm>

#include "game.hh"
#include "loader.hh"
#include "hud.hh"
#include "physicalobject.hh"
#include "asteroid.hh"
#include "trail.hh"
#include "projectile.hh"
#include "explosion.hh"
#include "humanplayer.hh"
#include "aiplayer.hh"
#include "planet.hh"
#include "sounds.hh"

using namespace irr;


//builds the game world
Game::Game(const char* path) {

	settings = readSettings("/settings.xml");

	/*
	const irr::core::dimension2d<irr::u32> res(settings.RESOLUTION_X, settings.RESOLUTION_Y);
	device = createDevice(video::EDT_OPENGL, res, 32,
			settings.DISPLAY_FULLSCREEN, false, false, &e);
			*/
	device.init(&e);
	driver = getDevice()->getVideoDriver();
	smgr = getDevice()->getSceneManager();

	hud = new Hud(this, getDevice());
	snd = new Sounds();

	e.initMouse(getDevice()->getCursorControl());

	timer = getDevice()->getTimer();
	
	HumanPlayer *p = new HumanPlayer(this, core::vector3df(0,0,0));
	setHuman(p);
	players.push_back(p);
	hud->setPlayer(p);

	readLevel(*this, path);
}

Game::~Game() {
	delete hud;
	delete snd;
}

void Game::applyGravitation(irr::f32 timeStep) {

	boost::ptr_vector<PhysicalObject>::iterator source, it;
	if(!objects.size()) return;
	for (source = objects.begin(); source != objects.end(); source++) {

		/* effects HumanPlayer
		core::vector3df acc = source->getPosition() - getHuman()->getPosition();
		acc.setLength(timeStep*settings.GRAVITATION_CONSTANT * (source->getMass()) /
				(acc.getLength()*acc.getLength()));
		getHuman()->setSpeed(getHuman()->getSpeed() + acc);
		*/

		for (it = asteroids.begin(); it != asteroids.end(); it++) {
			core::vector3df acc = source->getPosition() - it->getPosition();
			acc.setLength(timeStep*settings.GRAVITATION_CONSTANT * (source->getMass()) /
					(acc.getLength()*acc.getLength()));
			it->setSpeed(it->getSpeed() + acc);
		}

		for (it = projectiles.begin(); it != projectiles.end(); it++) {
			core::vector3df acc = source->getPosition() - it->getPosition();
			acc.setLength(timeStep*settings.GRAVITATION_CONSTANT * (source->getMass()) /
					(acc.getLength()*acc.getLength()));
			it->setSpeed(it->getSpeed() + acc);
		}
	}
}

void Game::checkCollisions() {

	boost::ptr_vector<Asteroid>::iterator a_it;
	boost::ptr_vector<Projectile>::iterator p_it;
	boost::ptr_vector<Player>::iterator pl_it;
	boost::ptr_vector<PhysicalObject>::iterator o_it;

	for (p_it = projectiles.begin(); p_it != projectiles.end(); p_it++) {

		//object hits
		for (o_it = objects.begin(); o_it != objects.end(); o_it++) {
			if (o_it->intersectsWith(*p_it))
				p_it->destruct();
		}

		//asteroid hits
		//for (a_it = asteroids.begin(); a_it != asteroids.end(); a_it++) {
		size_t i, i_max = asteroids.size();
		for (i = 0; i < i_max; i++) {
			if (asteroids.at(i).intersectsWith(*p_it)) {
				asteroids.at(i).hit(25);
				p_it->destruct();
			}
		}
		//player hits
		for (pl_it = players.begin(); pl_it != players.end(); pl_it++) {
			if (pl_it->intersectsWith(*p_it)) {
				pl_it->hit(20);
				p_it->destruct();
			}

		}
	}

	for (o_it = objects.begin(); o_it != objects.end(); o_it++) {
		size_t i, i_max = asteroids.size();
		for (i = 0; i < i_max; i++) {
			if (asteroids.at(i).intersectsWith(*o_it)) {
				asteroids.at(i).hit(10000);
			}
		}
		
		for (pl_it = players.begin(); pl_it != players.end(); pl_it++) {
			if (pl_it->intersectsWith(*o_it)) {
				pl_it->setSpeed(irr::core::vector3df(0,0,0));
				irr::core::vector3df dist = pl_it->getPosition()- o_it->getPosition();
				irr::f32 deltalength = (pl_it->getRadius()+o_it->getRadius()) - dist.getLength();
				dist.setLength(deltalength + 0.5f);
				pl_it->setPosition(pl_it->getPosition() + dist);
				pl_it->hit(50);
			}
		}

		/*
		if (o_it->intersectsWith(asteroids.at(i)))
			asteroids.at(i).hit(1000);
		if (o_it->intersectsWith(*pl_it))
			pl_it->hit(1000);
			*/
	}
}

bool checkRemove(PhysicalObject &obj){ return obj.getRemove(); }

void Game::updateObjects(irr::f32 timeStep) {

	players.erase_if(checkRemove);
	objects.erase_if(checkRemove);
	projectiles.erase_if(checkRemove);
	asteroids.erase_if(checkRemove);
	explosions.erase_if(checkRemove);
	trails.erase_if(checkRemove);

	applyGravitation(timeStep);

	checkCollisions();

	boost::ptr_vector<PhysicalObject>::iterator it;

	for (it = objects.begin(); it != objects.end(); it++)
		it->update(timeStep);
	for (it = players.begin(); it != players.end(); it++)
		it->update(timeStep);
	for (it = asteroids.begin(); it != asteroids.end(); it++)
		it->update(timeStep);
	for (it = explosions.begin(); it != explosions.end(); it++)
		it->update(timeStep);
	for (it = trails.begin(); it != trails.end(); it++)
		it->update(timeStep);

	boost::ptr_vector<Projectile>::iterator p_it;
	//irr::u32 time = timer->getTime();
	for (p_it = projectiles.begin(); p_it != projectiles.end(); p_it++) {
		if (p_it->getLifeTime() > settings.PROJECTILE_LIFETIME)
			p_it->setRemove(true);

		p_it->update(timeStep);
	}
}

void Game::run() {

	objects.push_back(new Planet(this, core::vector3df(0, 0, 0), 100, 500000));

	u32 then = timer->getTime();

	while(getDevice()->run() && !e.IsKeyDown(irr::KEY_ESCAPE)) {

		const u32 now = timer->getTime();

		if (getDevice()->isWindowActive()) {

			// limit fps to 100
			const f32 timeStep = (f32)(now - then) / 1000.f;
			if ( timeStep <= 0.01f ) {
				getDevice()->sleep(5);
				continue;
			}
			then = now;

			// updates
			e.updateMouse();
			updateObjects(timeStep);

			//draw scene
			driver->beginScene(true, true, video::SColor(255,255,255,255));
			smgr->drawAll();
			hud->draw();
			hud->update();
			driver->endScene();

			//window caption
			core::stringw str = "FPS:";
			str += driver->getFPS();
			str += " Projectiles: ";
			str += (int) projectiles.size();
			str += " Asteroids: ";
			str += (int) asteroids.size();
			getDevice()->setWindowCaption(str.c_str());
		}
		else
			getDevice()->sleep(100);
	}
}

