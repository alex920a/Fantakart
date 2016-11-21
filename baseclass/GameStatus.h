#ifndef GAMEST_H
#define GAMEST_H

#include <time.h>
#include <stdlib.h>
#include "../Utils/Defines.h"
#include "../Utils/Timer.h"
#include "../Objects3D/Kart.h"
#include "../Objects3D/Player.h"
#include "../Objects3D/World.h"
#include <SDL2/SDL.h>
#include "../Objects3D/Crystal.h"
#include "../Objects3D/PhotoId.h"
#include "../Objects3D/MiniMap.h"
#include "../Objects3D/Speedometer.h"
#include "../Objects3D/Hourglass.h"
#include "../Objects3D/Bomb.h"




class Texture_handler;
class CameraHandler;
class GameControl_handler;
class Sound_handler;
class Light_handler;


class GameStatus
{
public:
	int score;
	int fullscreen;


	Timer gameTime;
	State actualState;

	Texture_handler* th;
	CameraHandler* camera;
	GameControl_handler* ch;
	Sound_handler* sh;
	Light_handler* lh;

	Kart kart;
	int choosen_kart;  //0... MAX_CHARACTERS -1
	World world;
	std::vector<Crystal> crystals;
	std::vector<Hourglass> hourglasses;
	std::vector<Bomb> bombs;

	PhotoId myPhoto;
	MiniMap miniMap;
	Speedometer speedometer;

	bool losing;

	//constructor
	GameStatus(){LoadNewGame();}

	void LoadNewGame();
    void DetectCollisionKart(); //effettua un controllo sugli oggetti in collisione
    void Check_Collision_Crystal(int i);  //check collisione su singolo oggetto i
    void Check_Collision_Hourglass(int i);
    void Check_Collision_Bomb(int i);
    void Check_inHole(int i);
    void Check_collision_wall();





	virtual ~GameStatus(){};

};

#endif
