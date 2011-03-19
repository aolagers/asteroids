#ifndef ASTEROIDS_LOADER_HH
#define ASTEROIDS_LOADER_HH

#include "game.hh"
#include "hud.hh"

#include "settings.hh"

#include "asteroid.hh"
#include "humanplayer.hh"
#include "aiplayer.hh"

#include <algorithm>



template <typename OBJ>
void readAttributes(OBJ* p, irr::io::IrrXMLReader* reader) {
	 
		p->setMass(p->getMass()+reader->getAttributeValueAsInt("mass"));
		p->setHitPoints(p->getHitPoints()+reader->getAttributeValueAsInt("hp"));
		p->setRadius(p->getRadius()+reader->getAttributeValueAsInt("radius"));
		
		p->setPosition(p->getPosition()+irr::core::vector3df(reader->getAttributeValueAsInt("placex"),0,0));
		p->setPosition(p->getPosition()+irr::core::vector3df(0,reader->getAttributeValueAsInt("placey"),0));
		p->setPosition(p->getPosition()+irr::core::vector3df(0,0,reader->getAttributeValueAsInt("placez")));
		
		p->setSpeed(p->getSpeed()+irr::core::vector3df(reader->getAttributeValueAsInt("speedx"),0,0));
		p->setSpeed(p->getSpeed()+irr::core::vector3df(0,reader->getAttributeValueAsInt("speedy"),0));
		p->setSpeed(p->getSpeed()+irr::core::vector3df(0,0,reader->getAttributeValueAsInt("speedz")));
		
}

void readLevel(Game& game, std::string path) {

	std::string fullpath = PROJECT_DATA_DIR;
	fullpath.append(path);

	std::cout << "Loading level from " << fullpath << std::endl;
	irr::io::IrrXMLReader* reader = irr::io::createIrrXMLReader(fullpath.c_str());

	while(reader && reader->read()) {
		
		if(!strcmp("obj", reader->getNodeName())) {
			
			std::string type;
			if (reader->getAttributeValue("type")) type = reader->getAttributeValue("type");
				
			if(type == "asteroid") {
				Asteroid *p = new Asteroid(&game, irr::core::vector3df(100,0,0), irr::core::vector3df(0,0,0), 3);
				while(reader && reader->read() && strcmp("obj", reader->getNodeName())) {
					readAttributes(p, reader);
					if(int scale_temp = reader->getAttributeValueAsInt("scale")) {
						p->setScale(scale_temp);
					}
				}
				game.getAsteroids().push_back(p);
			}
			
			if(type == "humanplayer") {
				while(reader && reader->read() && strcmp("obj", reader->getNodeName())) {
					readAttributes(game.getHuman(), reader);
				}
			}
			
			if(type == "aiplayer") {
				AIPlayer* p = new AIPlayer(&game, irr::core::vector3df(0,0,0), game.getHuman());
				while(reader && reader->read() && strcmp("obj", reader->getNodeName())) {
					readAttributes(p, reader);
				}
				game.getPlayers().push_back(p);
			}
			
			if(type == "blackhole") {
				PhysicalObject* p = new PhysicalObject(&game);
				p->setNode(game.getSmgr()->addSphereSceneNode(50.f, 50));
				while(reader && reader->read() && strcmp("obj", reader->getNodeName())) {
					readAttributes(p, reader);
				}
				p->setRadius(50);
				game.getObjects().push_back(p);
			}
		}
		
		if(!strcmp("background", reader->getNodeName())) {
			std::string skypath = PROJECT_DATA_DIR;
			skypath.append(reader->getAttributeValue("path"));
			game.getSmgr()->addSkyDomeSceneNode(game.getDriver()->getTexture(skypath.c_str()), 32, 32, 1.0f, 2.0f);
		}
	}
	
	delete reader;
}

Settings readSettings(std::string path) {

	Settings s;

	std::string fullpath = PROJECT_DATA_DIR;
	fullpath.append(path);

	std::cout << "Loading settings from " << fullpath << std::endl;
	irr::io::IrrXMLReader* xml = irr::io::createIrrXMLReader(fullpath.c_str());

	irr::f32 d_tmp;
	irr::s32 i_tmp;

	while(xml && xml->read())
	{

		if (!strcmp("resolution", xml->getNodeName())) {
			if (i_tmp = xml->getAttributeValueAsInt("x")) s.RESOLUTION_X = i_tmp;
			if (i_tmp = xml->getAttributeValueAsInt("y")) s.RESOLUTION_Y = i_tmp;
		}

		else if (!strcmp("set", xml->getNodeName())) {

			i_tmp = xml->getAttributeValueAsInt("fullscreen");
			if (i_tmp == 1) s.DISPLAY_FULLSCREEN = true;

			i_tmp = xml->getAttributeValueAsInt("invert_pitch");
			if (i_tmp == 1 ) s.INVERT_PITCH = true;

			if (d_tmp = xml->getAttributeValueAsFloat("gravitation"))
			   s.GRAVITATION_CONSTANT = d_tmp;
			if (d_tmp = xml->getAttributeValueAsFloat("gun_cooldown"))
				s.GUN_COOLDOWN = d_tmp;
			if (d_tmp = xml->getAttributeValueAsFloat("maxfps"))
				s.MAX_FPS = d_tmp;

		}

		else if (!strcmp("projectile", xml->getNodeName())) {

			if (d_tmp = xml->getAttributeValueAsFloat("speed"))
				s.PROJECTILE_SPEED = d_tmp;
			if (d_tmp = xml->getAttributeValueAsFloat("lifetime"))
				s.PROJECTILE_LIFETIME = d_tmp;
		}

		else if (!strcmp("control", xml->getNodeName())) {
			s.TURN_SPEED= xml->getAttributeValueAsFloat("turn_speed");
			s.ACCELERATION_SPEED = xml->getAttributeValueAsFloat("acceleration_speed");
			s.MOUSE_SENSITIVITY= xml->getAttributeValueAsFloat("mouse_sens");
		}
	}

	std::cout << "Game settings:" << std::endl;
	std::cout << "fullscreen: " << s.DISPLAY_FULLSCREEN << std::endl;
	std::cout << "resolution: " << s.RESOLUTION_X << "x" << s.RESOLUTION_Y <<std::endl;
	std::cout << "gravitation: " << s.GRAVITATION_CONSTANT <<std::endl;
	std::cout << "invert: " << s.INVERT_PITCH <<std::endl;
	std::cout << "acceleration: " << s.ACCELERATION_SPEED <<std::endl;
	std::cout << "turn: " << s.TURN_SPEED <<std::endl;
	std::cout << "sens: " << s.MOUSE_SENSITIVITY <<std::endl;
	std::cout << "cooldown: " << s.GUN_COOLDOWN <<std::endl;
	std::cout << "projectile speed: " << s.PROJECTILE_SPEED <<std::endl;
	std::cout << "projectile lifetime: " << s.PROJECTILE_LIFETIME <<std::endl;

	delete xml;

	return s;
}

#endif
