#ifndef SOUNDHANDLER_H_
#define SOUNDHANDLER_H_

#include "baseclass/Handler.h"
#include <SDL2/SDL_mixer.h>

class Sound_handler : Handler
{
	public:
	 	 int current_song;
	 	 bool playmusic;
	 	 bool pausemusic;
	 	 bool playSoundeffect;
	 	 std::vector<Mix_Music *> musicThemes; //mp3
	 	 std::vector<Mix_Chunk* > musicEffects; //wav per effetti

	 	 Sound_handler();
	 	 Sound_handler(GameStatus* g);
	 	 virtual ~Sound_handler();

	 	 void Init();
	 	 bool LoadContents();
	 	 void PlaySong(int selection);
	 	 void PauseSong();
	 	 void StopSong();
	 	 void RewindSong();
	 	 void LoadSong(int selection); //funzione che stoppa la musica precendente e avvia quella selezionata

	 	 void PlayEffect(int selection);
	 	 void printSoundsInfo();
};

#endif //SOUNDHANDLER_H_
