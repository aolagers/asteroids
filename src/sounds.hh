#ifndef ASTEROIDS_SOUNDS_HH
#define ASTEROIDS_SOUNDS_HH

//#define NO_SOUNDS

#ifndef NO_SOUNDS
#include "SDL/SDL_mixer.h"
#endif
#include "game.hh"

class Sounds {

	public:
		Sounds();
		~Sounds();

		void playBackground();
		void playGunSound();
		void playDamageSound();
		void playExplosionSound(double distance);
		void playMoveSound(bool b);
		void playWarningSound(bool b);
		void loadWAVs();

	private:

#ifndef NO_SOUNDS
		Mix_Music *background;

		Mix_Chunk *gunSound;
		Mix_Chunk *explosion;
		Mix_Chunk *move;
		Mix_Chunk *warning;
		Mix_Chunk *damage;

		Uint16 audio_format; 
#endif
		
		int audio_rate;	
		int audio_channels;	
		int audio_buffers;	

};


#endif 
