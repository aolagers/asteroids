#include <cmath>
#include "hud.hh"
#include "asteroid.hh"
#include "humanplayer.hh"

using namespace irr;


Hud::Hud(Game *g, irr::IrrlichtDevice *dev): maxHealth(100.0),health(maxHealth),deltaHealth(maxHealth), maxGunCool(100.0),gunCool(maxGunCool),deltaGunCool(maxGunCool) {

	//HealthBar initial values
	barSpeedX = 0.0;
	barSpeedY = 0.0;
	barSpeedZ = 0.0;

	//GuiEnvironment setup
	env = dev->getGUIEnvironment();
	driver = dev->getVideoDriver();
	skin = env->getSkin();
	font = env->getFont(PROJECT_DATA_DIR "/bigfont.png");
	screenSize = driver->getScreenSize();

	//3D Compass vectors that are being projected on the screen
	endXAxis = core::vector3df(1,0,0);
	endYAxis = core::vector3df(0,-1,0);
	endZAxis = core::vector3df(0,0,-1);

	//Position for 3D Compass
	start = core::position2d<s32>(screenSize.Width/10,9*screenSize.Height/10);

	//HealtBar backgrounds
	
	healthRecX1 = 4*screenSize.Width/5;            
	healthRecX2 = 19*screenSize.Width/20;
	healthRecY1 = 9*screenSize.Height/10;
	healthRecY2 = 19*screenSize.Height/20;
	
	healthInnerRecX1 = 4*screenSize.Width/5+5;
	healthInnerRecY1 = 9*screenSize.Height/10+5;
	healthInnerRecX2 = 19*screenSize.Width/20-5;
	healthInnerRecY2 = 19*screenSize.Height/20-5;

	//HealthBar initial values
	healthBarX1 = 4*screenSize.Width/5+5;
	healthBarY1 = 9*screenSize.Height/10+5;
	healthBarY2 = 19*screenSize.Height/20-5;

	//powermeter
	powerMeterOutline = core::rect<s32>(4*screenSize.Width/5, 16*screenSize.Height/20, 19*screenSize.Width/20, 17*screenSize.Height/20);
	powerMeterBackground = core::rect<s32>(4*screenSize.Width/5 + 5, 16*screenSize.Height/20 + 5, 19*screenSize.Width/20 - 5, 17*screenSize.Height/20 - 5);

	//Initial values for X-directions speedBar		
	speedXBarX1 = screenSize.Width/100;
	speedXBarY1 = screenSize.Height/10;
	speedXBarX2 = screenSize.Width/100;
	speedXBarY2 = 9*screenSize.Height/10;
	initH = screenSize.Height/10;
	initW = screenSize.Width/100;
	intervalH = (8*screenSize.Width/10)/21;

	//initial values for Y-direction speedBar
	speedYBarX1 = screenSize.Width/10;
	speedYBarY1 = screenSize.Height/100;
	speedYBarX2 = 9*screenSize.Width/10;
	speedYBarY2 = screenSize.Height/100;
	initHY = screenSize.Height/100;
	initWY = screenSize.Width/10;


	//initial values for Z-direction speedBar
	intervalV = (8*screenSize.Height/10)/21;
	speedZBarX1 = 99*screenSize.Width/100;
	speedZBarY1 = screenSize.Height/10;
	speedZBarX2 = 99*screenSize.Width/100;
	speedZBarY2 = 9*screenSize.Height/10;
	initHZ = screenSize.Height/10;
	initWZ = 99*screenSize.Width/100;

	skin->setFont(font);
	skin->setColor(irr::gui::EGDC_BUTTON_TEXT, video::SColor(255, 255, 0, 255));

	//Drawing textelements for velocities
	textElements.spd_z = env->addStaticText(L"foo",	irr::core::rect<irr::s32>((s32)(22*screenSize.Width/25),
				(s32)(47.9*screenSize.Height/100),(s32)(22*screenSize.Width/25 + 100),(s32)(47.9*screenSize.Height/100 + 30)));
	textElements.spd_x = env->addStaticText(L"foo",irr::core::rect<irr::s32>((s32)(screenSize.Width/25),
				(s32)(47.9*screenSize.Height/100),(s32)(screenSize.Width/25 + 100),(s32)(47.9*screenSize.Height/100 + 30)));
	textElements.spd_y = env->addStaticText(L"foo",	irr::core::rect<irr::s32>(43*screenSize.Width/100,
				screenSize.Height/20,43*screenSize.Width/100 + 100,screenSize.Height/20 + 30));
	textElements.spd_tot = env->addStaticText(L"foo",irr::core::rect<irr::s32>(48*screenSize.Width/100,
				9*screenSize.Height/10,48*screenSize.Width + 30,9*screenSize.Height/10 + 100));
	textElements.spd_y->setTextAlignment(irr::gui::EGUIA_LOWERRIGHT, irr::gui::EGUIA_LOWERRIGHT);

	mode = env->addStaticText(L"foo",irr::core::rect<irr::s32>(screenSize.Width/4,9*screenSize.Height/10,2*screenSize.Width/4,screenSize.Height));	
	gui::IGUIFont* font2 = env->getBuiltInFont();
		
	//Intialaizing velocity displays	
	relativeVelocityAI = env->addStaticText(L"foo",irr::core::rect<irr::s32>(600,600,630,700));
	relativeVelocityAI->setOverrideFont(font2);
	relativeVelocityAI->setVisible(false);
	relativeVelocityAI->setOverrideColor(video::SColor(255,0,0,255));

	relativeVelocityAsteroid = env->addStaticText(L"foo",irr::core::rect<irr::s32>(300,300,330,400));
	relativeVelocityAsteroid->setOverrideFont(font2);
	relativeVelocityAsteroid->setVisible(false);
	relativeVelocityAsteroid->setOverrideColor(video::SColor(255,255,255,0));


	//Drawing the arrows for speedBars
	env->addImage(driver->getTexture(PROJECT_DATA_DIR "/crosshair.png"),
			core::position2d<int>(g->getSettings().RESOLUTION_X/2 - 48, g->getSettings().RESOLUTION_Y/2 - 48));

	env->addImage(driver->getTexture(PROJECT_DATA_DIR "/arrow1.png"),
			core::position2d<int>((s32)48.5*screenSize.Width/100,(s32)screenSize.Height/30));

	env->addImage(driver->getTexture(PROJECT_DATA_DIR "/arrow2.png"),
			core::position2d<int>((s32)47.5*screenSize.Width/50,(s32)48.1*screenSize.Height/100));	

	env->addImage(driver->getTexture(PROJECT_DATA_DIR "/arrow3.png"),
			core::position2d<int>((s32)screenSize.Width/40,(s32)48.1*screenSize.Height/100));

}




Asteroid* getTargetAsteroid(boost::ptr_vector<Asteroid>* asteroids, core::vector3df position) {
	core::vector3df target = core::vector3df(0,0,0);
	Asteroid* as = NULL;
	if(!asteroids->empty()){
		double distance = (asteroids->at(0).getPosition() - position).getLength();
		target = asteroids->at(0).getPosition();
		as = &asteroids->at(0);
		for(unsigned i = 0; i < asteroids->size(); ++i){
			if((asteroids->at(i).getPosition()-position).getLength()<distance){
				distance = (asteroids->at(i).getPosition()-position).getLength();
				target = asteroids->at(i).getPosition();
				as = &asteroids->at(i);
			}
		}
	}
	
	return as;
}


Player* getTargetPlayer(boost::ptr_vector<Player>* players, core::vector3df position) {
	core::vector3df target = core::vector3df(0,0,0);
	Player* tarPlay = NULL;
	double distance = 0,help;
	for(unsigned i = 0; i < players->size(); ++i){
		help = (players->at(i).getPosition()-position).getLength();
		if(help){
			if(distance == 0) { distance = help; target = players->at(i).getPosition(); tarPlay = &players->at(i); }
			else {
				if(help < distance) { distance = help; target = players->at(i).getPosition(); tarPlay = &players->at(i); }
			}
		}
	}
	
	return tarPlay;
}

template <typename T> void drawTarget(core::dimension2d<irr::u32> screenSize,core::vector3df X,core::vector3df Y,core::vector3df Z,
		T target,core::vector3df position, video::IVideoDriver *driver,video::SColor color, irr::gui::IGUIStaticText *relativeVelocity, core::vector3df playerSpeed){
    relativeVelocity->setVisible(false);
    
	core::vector3df vecN = target->getPosition()-position;
	core::vector3df vec = vecN;
	vecN.normalize();	//normalized vector pointting to target

	f32 projectionX = vecN.dotProduct(X);          //Transformation to"Player-space"
	f32 projectionY = vecN.dotProduct(Y);
	f32 projectionZ = vecN.dotProduct(Z);

	f32 XPOS = screenSize.Width/2 - projectionX* screenSize.Width/2;	//Drawpositions on the screen
	f32 YPOS = screenSize.Height/2 - projectionY*screenSize.Height/2;

	core::vector2df point = core::vector2df(-projectionX,-projectionY).normalize();//normalized vector to indicate guides heading on the screen
	
	//relativevelocity display updates
	core::stringw spd_txt = ""; spd_txt += (int)(target->getSpeed() - playerSpeed).getLength();
	relativeVelocity->setText(spd_txt.c_str());
	relativeVelocity->setRelativePosition(core::position2d<int>(XPOS+20,YPOS-10));
    

	if(projectionZ>0.7){	//execute in case player can see the target
		if(vec.getLength()>4000) { 		//if target is really faraway (5000) set marker (Could make this one of the settings)
			driver->draw2DLine(core::position2d<int>((s32)(XPOS+10),(s32)(YPOS+5)),core::position2d<int>((s32)(XPOS-10),(s32)(YPOS+5)),color);
			driver->draw2DLine(core::position2d<int>((s32)(XPOS+10),(s32)(YPOS+5)),core::position2d<int>((s32)(XPOS),(s32)(YPOS-12)),color);
			driver->draw2DLine(core::position2d<int>((s32)(XPOS),(s32)(YPOS-12)),core::position2d<int>((s32)(XPOS-10),(s32)(YPOS+5)),color);
			relativeVelocity->setVisible(true);//if we are sufficiently far away set relative velocity display on
		}                                            
	}
	else{			//if player isn't looking at target point to target
		driver->draw2DLine(core::position2d<int>((s32)(screenSize.Width/2 + 300*point.X),(s32)(screenSize.Height/2 + 300*point.Y)),
				core::position2d<int>((s32)(screenSize.Width/2 + 330*point.X),(s32)(screenSize.Height/2 + 330*point.Y)),color);
	}
}


void Hud::update() {


	health = player->getHitPoints();

	healthBarX2 = (s32)(health/2/maxHealth*(19*screenSize.Width/20-5 -(4*screenSize.Width/5+5)) + 4*screenSize.Width/5+5);        
	core::vector3df relSpeed = player->getRelativeSpeed();
	core::stringw spd_txt;
	//gunCool = player->getGunCool();
	//gunCoolBarX2 = (s32)(gunCool/maxGunCool*(19*screenSize.Width/20-5 -(4*screenSize.Width/5+5)) + 4*screenSize.Width/5+5);

	//updating health bar
	if(health != deltaHealth){
		double delta = health - deltaHealth;
		if(delta < 0) deltaHealth -= 0.1;
		if(delta > 0) deltaHealth += 0.1;       
	}

	//updating gunCool bar
	/*
	if(gunCool != deltaGunCool) {
		double deltaGun = gunCool - deltaGunCool;
		if(deltaGun < 0) deltaGunCool -= 0.1;
		if(deltaGun > 0) deltaGunCool += 0.1;
	}
	*/

	//updating speed bars
	//change at bars is small if change in value is small and other way around       
	if(relSpeed.X != barSpeedX){
		double deltaSpeedX = barSpeedX - relSpeed.X;
		barSpeedX += -deltaSpeedX/10;
	}
	if(relSpeed.Y != barSpeedY){
		double deltaSpeedY = barSpeedY -relSpeed.Y;
		barSpeedY += -deltaSpeedY/10;

	}
	if(relSpeed.Z != barSpeedZ){
		double deltaSpeedZ = barSpeedZ - relSpeed.Z;
		barSpeedZ += -deltaSpeedZ/10;

	}


	//speed value update
	spd_txt = ""; spd_txt += (int)relSpeed.X;
	textElements.spd_x->setText(spd_txt.c_str());

	spd_txt = ""; spd_txt += (int)relSpeed.Y;
	textElements.spd_y->setText(spd_txt.c_str());

	spd_txt = ""; spd_txt += (int)relSpeed.Z;
	textElements.spd_z->setText(spd_txt.c_str());

	spd_txt = ""; spd_txt += (int)player->getSpeed().getLength();
	textElements.spd_tot->setText(spd_txt.c_str());

	if(player->getMode() ){ 
                           
                           core::stringw txt = "Velocity Mode";
                           mode->setText(txt.c_str());
                           }
	else {
            
          core::stringw tx = "Inertial mode";     
          mode->setText(tx.c_str());
}

	//health bar and it's background drawing
	driver->draw2DRectangle(video::SColor(100, 220, 30, 150), core::rect<s32>(healthRecX1,healthRecY1,healthRecX2,healthRecY2));			
	driver->draw2DRectangle(video::SColor(255, 100, 50, 100), core::rect<s32>(healthInnerRecX1,healthInnerRecY1,healthInnerRecX2,healthInnerRecY2));
	driver->draw2DRectangle(video::SColor(180,(u32)( 255-health/2*2.55),(u32)(health/2*2.55), 0),core::rect<s32>(healthBarX1,healthBarY1,healthBarX2,healthBarY2));

	/*
	driver->draw2DRectangle(video::SColor(100, 220, 30, 150), core::rect<s32>(healthRecX1,healthRecY1 - gunBarDisplacement,healthBarX2,healthRecY2 - gunBarDisplacement));			
	driver->draw2DRectangle(video::SColor(255, 100, 50, 100), core::rect<s32>(healthInnerRecX1,healthInnerRecY1 - gunBarDisplacement,healthInnerRecX2,healthInnerRecY2 - gunBarDisplacement));
	driver->draw2DRectangle(video::SColor(200,200,0, 200),core::rect<s32>(healthBarX1,healthBarY1 - gunBarDisplacement,healthBarX1+power,healthBarY2 - gunBarDisplacement));
	*/

	/* Update and draw powermeter*/
	double power = player->getPower() * powerMeterBackground.getWidth() / 200.0;
	//std::cout << powerMeterValue << " -- " << powerMeterBackground << std::endl;
	powerMeterValue = core::rect<s32>(4*screenSize.Width/5 + 5, 16*screenSize.Height/20 + 5, 4*screenSize.Width/5  + power , 17*screenSize.Height/20 - 5);
	driver->draw2DRectangle(video::SColor(100, 220, 30, 150), powerMeterOutline);			
	driver->draw2DRectangle(video::SColor(255, 100, 50, 100), powerMeterBackground);
	driver->draw2DRectangle(video::SColor(200,200,   0, 200), powerMeterValue);

	//Speed bar drawing   
	driver->draw2DLine(core::position2d<int>(speedYBarX1,speedYBarY1),core::position2d<int>(speedYBarX2,speedYBarY2),video::SColor(255,255,0,255));
	double transY = ((double)((int)barSpeedY%50))/50*intervalH;
	for(unsigned i = 0; i < 21; ++i){
		driver->draw2DLine(core::position2d<s32>((s32)(initWY + (0.5 + i)*intervalH + transY),initHY),
				core::position2d<s32>((s32)(initWY + (0.5 +i)*intervalH + transY),(s32)(initHY + 10)),video::SColor(255,255,0,255));
	}

	driver->draw2DLine(core::position2d<int>(speedZBarX1,speedZBarY1),core::position2d<int>(speedZBarX2,speedZBarY2),video::SColor(255,255,0,255));
	double transZ = -((double)((int)barSpeedZ%50))/50*intervalV;
	for(unsigned i = 0; i < 21; ++i){
		driver->draw2DLine(core::position2d<s32>((s32)(initWZ),(s32)(initHZ + (0.5 + i)*intervalV + transZ)),
				core::position2d<s32>((s32)(initWZ - 10),(s32)(initHZ + (0.5 + i)*intervalV + transZ)),video::SColor(255,255,0,255));
	}

	driver->draw2DLine(core::position2d<int>(speedXBarX1,speedXBarY1),core::position2d<int>(speedXBarX2,speedXBarY2),video::SColor(255,255,0,255));
	double trans = -((double)((int)barSpeedX%50))/50*intervalV;
	for(unsigned i = 0; i < 21; ++i){
		driver->draw2DLine(core::position2d<s32>((s32)initW,(s32)(initH + (0.5 + i)*intervalV + trans)),
				core::position2d<s32>((s32)(initW + 10),(s32)(initH + (0.5 + i)*intervalV + trans)),video::SColor(255,255,0,255));
	}




	//calculating Compass' axis
	core::vector3df forwa = player->getForward();
	core::vector3df Z = forwa.normalize();
	core::vector3df up = player->getCam()->getUpVector();
	core::vector3df Y = up.normalize();
	core::vector3df Y1 = Z.crossProduct(Y);
	core::vector3df X = Y1.normalize();

	//Drawing axis
	driver->draw2DLine(start,start + core::position2d<s32>((s32)(100*X.X),(s32)(100*X.Y)),video::SColor(255,200,0,255));
	driver->draw2DLine(start,start + core::position2d<s32>((s32)(-100*Y.X),(s32)(-100*Y.Y)),video::SColor(255,255,0,200));
	driver->draw2DLine(start,start + core::position2d<s32>((s32)(100*Z.X),(s32)(100*Z.Y)),video::SColor(255,255,0,255));



	//Targetting/guiding system
	core::vector3df posit = player->getPosition();
	Asteroid* as = getTargetAsteroid(&player->getGame()->getAsteroids(),posit);	//Asteroid to be targetted
	Player* tarPlay = getTargetPlayer(&player->getGame()->getPlayers(),posit); //Player to be targetted
	video::SColor playerColor = video::SColor(255,0,0,255);		//color for player targets
	video::SColor asteroidColor = video::SColor(255,255,255,0);	//color for asteroid targets


	if(as){
		drawTarget(screenSize, X, Y, Z, as, posit, driver,asteroidColor,relativeVelocityAsteroid,player->getSpeed());
		if((as->getPosition() - posit).getLength() < 400) player->getGame()->getSounds()->playWarningSound(true);
		else 	player->getGame()->getSounds()->playWarningSound(false);

	}

	if(tarPlay){
		drawTarget(screenSize, X, Y, Z, tarPlay, posit, driver, playerColor,relativeVelocityAI,player->getSpeed());
        
  }

}
/*
void Hud::operator()() {
	u32 then = g->getTimer()->getTime();
	while(g->getDevice()->run()) {
		const u32 now = g->getTimer()->getTime();
		const f32 timeStep = (f32)(now - then) / 1000.f;
		if (now-then < (1000.f / g->settings.MAX_FPS)) continue;
		then = now;

		update();
		draw();
	}
}
*/
