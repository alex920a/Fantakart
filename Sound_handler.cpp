#include "Sound_handler.h"

Sound_handler::Sound_handler()
{
	current_song = 0;
	playSoundeffect = playmusic = true;
	pausemusic = false;
}

Sound_handler::Sound_handler(GameStatus* g): Handler(g)
{
	current_song = 0;
	playSoundeffect = playmusic = true;
	pausemusic = false;
}

Sound_handler::~Sound_handler(){}




void Sound_handler::Init()
{
	current_song = 0;
	playSoundeffect = false;
	playmusic = true;
	pausemusic = false;
	musicThemes.reserve(NUM_MAX_SONGS);
	musicEffects.reserve(NUM_MAX_SONGS);

	Mix_AllocateChannels(2); //alloco due canali per l'audio
	if(!LoadContents())
		std::cout<<"Errore nel caricamento degli audio\n";
}

bool Sound_handler::LoadContents()
{



	musicThemes.push_back(Mix_LoadMUS(WARPED_THEME.c_str()))  ;
	if(musicThemes.at(0) == NULL)
		return false;

	musicThemes.push_back(Mix_LoadMUS(BOSS_RACE.c_str())) ;
	if(musicThemes.at(1) == NULL)
		return false;


	musicThemes.push_back(Mix_LoadMUS(SUPERMARIO.c_str())) ;
	if(musicThemes.at(2) == NULL)
		return false;


	musicThemes.push_back(Mix_LoadMUS(CHAR_SEL.c_str()))  ;
		if(musicThemes.at(3) == NULL)
			return false;





	musicThemes.resize(4);


	//carico file wav effetti
	musicEffects.push_back(Mix_LoadWAV(PAUSE_WAV.c_str()));
	if(musicEffects.at(0) == NULL)
		return false;

	musicEffects.push_back(Mix_LoadWAV(CRYSTAL_WAV.c_str()));
	if(musicEffects.at(1) == NULL)
		return false;

	musicEffects.push_back(Mix_LoadWAV(PORTAL_WAV.c_str()));
	if(musicEffects.at(2) == NULL)
		return false;

	musicEffects.push_back(Mix_LoadWAV(BOMB_WAV.c_str()));
	if(musicEffects.at(3) == NULL)
		return false;

	musicEffects.push_back(Mix_LoadWAV(HOURGLASS_WAV.c_str()));
	if(musicEffects.at(4) == NULL)
		return false;





	musicEffects.resize(5);



	return true;

}

void Sound_handler::PlaySong(int selection)
{

	if(Mix_PlayingMusic() == 0 )
	{
		Mix_PlayMusic(musicThemes.at(selection),0);
		current_song = selection;
	}


}

void Sound_handler::PlayEffect(int selection)
{
	if(Mix_PlayChannel(-1,musicEffects.at(selection),0) == -1)
	{
		//std::cout<<"non posso riprodurre effetto:\n";
	}
	else
		Mix_PlayChannel(-1,musicEffects.at(selection),0);
}

void Sound_handler::RewindSong()
{
	Mix_RewindMusic();
}

void Sound_handler::PauseSong()
{
	if(Mix_PlayingMusic() == 0 )
	{
		Mix_PauseMusic();
	}

	if(Mix_PlayingMusic() == 0 )
	{
		Mix_ResumeMusic();
	}

}

void Sound_handler::StopSong()
{
	Mix_HaltMusic();

}

void Sound_handler::printSoundsInfo()
{
	std::cout<<"Tot loaded songs: "<<musicThemes.size()<<"\n"<<std::endl;
	std::cout<<"Tot loaded effects: "<<musicEffects.size()<<"\n"<<std::endl;
}

void Sound_handler::LoadSong(int selection)
{
	StopSong();
	PlaySong(selection);
	RewindSong();
}
