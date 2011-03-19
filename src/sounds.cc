#include "sounds.hh"
//#define NO_SOUNDS
#ifndef NO_SOUNDS

/*
	Channels are arranged so that:
	0: moving
	1: backround
	2: exlosion
	3: gunsound
	4: proximity warning
	5: damage
*/

Sounds::Sounds() {

	Mix_Chunk *background = NULL; 
	int audio_rate = 22050;	
	Uint16 audio_format = AUDIO_S16SYS; 	
	int audio_channels = 2;			
	int audio_buffers = 256;

	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		std::cout << "Unable to initialize audio: " << Mix_GetError() << std::endl;
	}

	loadWAVs();

	playBackground();

}

void Sounds::loadWAVs() {

	background = Mix_LoadMUS(PROJECT_DATA_DIR "/Eventful-Moolkye-1518.wav");
	if(background == NULL) { std::cout<<"Unable to load WAV file: " << Mix_GetError()<< std::endl; }

	gunSound = Mix_LoadWAV(PROJECT_DATA_DIR "/gunsound03.wav");
	if(gunSound == NULL) { std::cout<<"Unable to load WAV file: " << Mix_GetError()<< std::endl; }
	Mix_VolumeChunk(gunSound, MIX_MAX_VOLUME/2);

	explosion = Mix_LoadWAV(PROJECT_DATA_DIR "/explosion2.wav");
	if(explosion == NULL) { std::cout<<"Unable to load WAV file: "<<Mix_GetError() <<std::endl; }

	move = Mix_LoadWAV(PROJECT_DATA_DIR "/turn.wav");
	if(move == NULL) { std::cout<<"Unable to load WAV file: " << Mix_GetError() << std::endl; }

	warning = Mix_LoadWAV(PROJECT_DATA_DIR "/warning.wav");
	if(warning == NULL) { std::cout << "Unable to load WAV file: " << Mix_GetError() << std::endl; }

	damage= Mix_LoadWAV(PROJECT_DATA_DIR "/damage.wav");
	if(warning == NULL) { std::cout << "Unable to load WAV file: " << Mix_GetError() << std::endl; }

	int channel = Mix_PlayChannel(0, move, -1);
	if(channel == -1) {
		std::cout<<"Unable to play WAV file: " << Mix_GetError()<<std::endl;
	}
	Mix_Pause(0);
	Mix_VolumeChunk(move,MIX_MAX_VOLUME/8);

	int channel1 = Mix_PlayChannel(4, warning, -1);
	if(channel1 == -1) {
		std::cout<<"Unable to play WAV file: " << Mix_GetError()<<std::endl;
	}
	Mix_Pause(4);
	Mix_VolumeChunk(move,MIX_MAX_VOLUME/6);
}


Sounds::~Sounds(){
	Mix_FreeMusic(background);

	Mix_FreeChunk(gunSound);
	Mix_FreeChunk(explosion);
	Mix_FreeChunk(move);
	Mix_FreeChunk(warning);

	Mix_CloseAudio();
}

void Sounds::playGunSound() {

	int channel = Mix_PlayChannel(3, gunSound, 0);
	if(channel == -1) { std::cout<<"Unable to play WAV file: " << Mix_GetError()<<std::endl; }	
}

void Sounds::playDamageSound() {
	int channel = Mix_PlayChannel(5, damage, 0);
	if(channel == -1) { std::cout<<"Unable to play WAV file: " << Mix_GetError()<<std::endl; }	
}


void Sounds::playBackground(){
	Mix_PlayMusic(background, -1);
}


void Sounds::playExplosionSound(double distance) {

	distance /= 700;

	Mix_VolumeChunk(explosion, MIX_MAX_VOLUME/distance);

	int channel = Mix_PlayChannel(2, explosion, 0);
	if (channel == -1)
		std::cout<<"Unable to play WAV file: "<<Mix_GetError()<<std::endl;

}

	void Sounds::playMoveSound(bool b) {
		if (b)
			Mix_Resume(0);
		else
			Mix_Pause(0);
	}

	void Sounds::playWarningSound(bool b) {
		if (b)
			Mix_Resume(4);
		else
			Mix_Pause(4);
	}

#else
Sounds::Sounds() { }
void Sounds::loadWAVs() { }
Sounds::~Sounds(){ }
void Sounds::playGunSound() { }
void Sounds::playDamageSound() { }
void Sounds::playBackground(){ }
void Sounds::playExplosionSound(double) { }
void Sounds::playMoveSound(bool) { }
void Sounds::playWarningSound(bool) { }
#endif
