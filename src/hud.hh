#ifndef ASTEROIDS_HUD_HH
#define ASTEROIDS_HUD_HH

#include "settings.hh"
#include "humanplayer.hh"
//#include "game.hh"

class Hud {

	public:
		/**
		 * Creates a new Hud
		 * Head Up Display is 2D visual interface that player can use as an aid in fight against enemy ships and asteroids
		 * HUD provides players own absolut velocities numerically as well as graphically, 3D compass for orientaion, 
		 * guiding when player is far away from nearest AI/Asteroid or facing the wrong way. Guiding system provides also relative velocities 
		 * between player and nearest AI/Asteroid. HUD aloso indicates the mode currently used VELOCITY/INERTIAL. Health bar tells player how much damage 
		 * the ship has sufferd and gun bar tells the status of the weapons (player can just shoot continuosly beacous guns will overheat and stall).
		 * @param pointer to a game where the player is
		 * @param IrrlichtDevice controlling the game
		 */
		Hud(Game *g, irr::IrrlichtDevice *dev);


		/**
		 * Sets player i.e. tells HUD the player whos information will be played
		 * @param Pointer to a HumenPlayer whos information will be played
		 */
		void setPlayer(HumanPlayer *p) {
			player = p;
		}
		
		/**
		 * Allmost all calculations regarding the HUD are done here. This Function has three helper function that are inplemented in hud.cc (getTargetAsteroid,
         * getTargetPlayer and drawTarget) THIS SHOULD BE RUN AFTER HUD::draw(), otherwise it won't render contents
		 */
		void update();

		/**
		 * This has to be called if something is rendered. HAS TO BE CALLED BEFORE HUD::update().
		 */
		void draw() const {
			env->drawAll();
		}
		
	//	void operator()();
		

	private:

		Game *g; 

		double maxHealth;
		double health;  //change this if you want to change health initial value is 100
		double deltaHealth;
		double barSpeedX;
		double barSpeedY;
		double barSpeedZ;
        
		irr::gui::IGUIEnvironment *env;
		irr::video::IVideoDriver *driver;
		irr::gui::IGUISkin *skin;
		irr::gui::IGUIFont *font;
		
		irr::core::dimension2d<irr::u32> screenSize;
	
		HumanPlayer *player;
    
		irr::core::rect<irr::s32> powerMeterOutline;
		irr::core::rect<irr::s32> powerMeterBackground;
		irr::core::rect<irr::s32> powerMeterValue;

		irr::s32 healthRecX1;
		irr::s32 healthRecX2;
		irr::s32 healthRecY1;
		irr::s32 healthRecY2;
		
		irr::s32 healthInnerRecX1;
		irr::s32 healthInnerRecY1;
		irr::s32 healthInnerRecX2;
		irr::s32 healthInnerRecY2;
		
		irr::s32 healthBarX1;
		irr::s32 healthBarY1;
		irr::s32 healthBarX2;
		irr::s32 healthBarY2;   

          
		irr::s32 speedXBarX1;
		irr::s32 speedXBarY1;
		irr::s32 speedXBarX2;
		irr::s32 speedXBarY2;  
		irr::s32 initH;
		irr::s32 initW;
		irr::s32 intervalH;
        
        
		irr::s32 intervalV;
		irr::s32 speedZBarX1;
		irr::s32 speedZBarY1;
		irr::s32 speedZBarX2;
		irr::s32 speedZBarY2;
		irr::s32 initHZ;
		irr::s32 initWZ;
        
		irr::s32 speedYBarX1;
		irr::s32 speedYBarY1;
		irr::s32 speedYBarX2;
		irr::s32 speedYBarY2;
		irr::s32 initHY;
		irr::s32 initWY;
		
		irr::s32 gunBarDisplacement;
		irr::s32 gunCoolBarX2;
		double maxGunCool;
		double gunCool; //change this if you want to change the gunBar
		double deltaGunCool;
		
		irr::core::vector3df endXAxis;
		irr::core::vector3df endYAxis;
		irr::core::vector3df endZAxis;
		irr::core::position2d<irr::s32> start;
		


		struct {
			irr::gui::IGUIStaticText *spd_z;
			irr::gui::IGUIStaticText *spd_x;
			irr::gui::IGUIStaticText *spd_y;
			irr::gui::IGUIStaticText *spd_tot;
		} textElements;

		irr::gui::IGUIStaticText *mode;
		irr::gui::IGUIStaticText *relativeVelocityAI;
		irr::gui::IGUIStaticText *relativeVelocityAsteroid;
};

#endif




