#ifndef DEFINES_H_
#define DEFINES_H_

#include <string>


#define SCR_H 700
#define SCR_W 700  // altezza e larghezza viewport (in pixels) l'ho messa quadrata cosi era piu bella con le textures
#define PHYS_SAMPLING_STEP 10 //numero di millsec che un passo di fisica simula
#define FPS_SAMPLING 3000
#define DEFAULT_PTSIZE  30

/* COSTANTI PER IL MONDO */
#define S_FLOOR_SIZE 30

#define NUM_MAX_CHARACTERS 3
#define NUM_MAX_SONGS 20
#define TIME_LEFT 50
#define NUM_MAX_CRYSTALS 20
#define NUM_MAX_HOURGLASSES 5
#define NUM_MAX_HOLES 4
#define NUM_MAX_BOMBS 5
#define MAX_TIME_TURBO 2
#define CAMERA_TYPE_MAX 3



enum State {LOADING,CHARACTERS, PLAYING, PAUSE, END, QUIT};
enum Camera_state {BEHIND, TOP, LATERAL};


/* TEXTURES*/
#define TEX_PAUSE 0
#define TEX_MAIN 1
#define TEX_CRASH 2
#define TEX_CORTEX 3
#define TEX_OXIDE 4
#define TEX_END_LOSE 5
#define TEX_SKY 6
#define TEX_PHOTO 7
#define TEX_SPEEDOMETER 8
#define TEX_ARROW 9
#define TEX_END_WIN 10
#define TEX_MAP_GRID 11
#define TEXT_TIMER 12
#define TEXT_SCORE 13
#define TEX_CORTEX_BODY 14
#define TEX_OXIDE_BODY 15
#define TEX_CRASH_BODY 16
#define TEX_HOLE 17
#define TEX_ROAD 18
#define TEX_WALL 19
#define TEX_CHESS 20



static const std::string CIRCUIT =  "res/textures/circuit.jpg";
static const std::string PAUSE_SCREEN =  "res/textures/pause1.jpg";
static const std::string MAIN_SCREEN =  "res/textures/loading.jpeg";
static const std::string ROAD = "res/textures/roadTexture.jpg";
static const std::string CRASH_KART = "res/textures/crashcar.jpg";
static const std::string CRASH_BODY = "res/models/Crash/body.jpg";
static const std::string CORTEX_KART = "res/textures/cortexcar.jpg";
static const std::string CORTEX_BODY = "res/models/Cortex/body.jpg";
static const std::string OXIDE_KART = "res/textures/Noxidecar.jpg";
static const std::string OXIDE_BODY = "res/models/Oxide/body.jpg";
static const std::string END_SCREEN_LOSE = "res/textures/endgame.jpg";
static const std::string END_SCREEN_WIN = "res/textures/win.jpg";
static const std::string SKY_TEX = "res/textures/sky.jpg";
static const std::string MYPHOTO = "res/textures/myPhoto.jpg";
static const std::string SPEEDOMETER = "res/textures/speedometer.jpeg";
static const std::string ARROW = "res/textures/arrow.jpeg";
static const std::string MAP_GRID = "res/textures/mapGrid.jpg";
static const std::string HOLE = "res/textures/hole.jpg";
static const std::string WALL = "res/textures/wall.jpg";
static const std::string CHESS = "res/textures/scacchiera.jpg";



/*SOUNDS */


static const std::string SUPERMARIO =  "res/sounds/supermario_theme.mp3";
static const std::string BOSS_RACE =  "res/sounds/boss_race.mp3";
static const std::string WARPED_THEME =  "res/sounds/crash_warped.mp3";
static const std::string CHAR_SEL = "res/sounds/char_sel.mp3";
static const std::string PAUSE_WAV ="res/sounds/pause.wav";
static const std::string CRYSTAL_WAV = "res/sounds/smw_coin.wav";
static const std::string PORTAL_WAV = "res/sounds/portal.wav";
static const std::string BOMB_WAV = "res/sounds/bomb.wav";
static const std::string HOURGLASS_WAV = "res/sounds/hourglass.wav";



#endif /*DEFINES_H_*/
