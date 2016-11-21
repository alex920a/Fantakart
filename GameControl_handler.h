#ifndef GAMECONTROLHANDLER_H_
#define GAMECONTROLHANDLER_H_

#include "baseclass/Handler.h"
#include "baseclass/Model3D.h"

#include "CameraHandler.h"
#include "Light_handler.h"
#include "../Utils/polygons.h"
#include <SDL2/SDL_ttf.h>
#include "Utils/GLText.h"
#include <stdio.h>
#include <stdlib.h>

class GameControl_handler : Handler
{
	public:
		GLuint screen_name; //gllist
		GLuint chess_list;  //display list
		TTF_Font* font;




		GameControl_handler(GameStatus* g): Handler(g){ screen_name= chess_list= 0; font = NULL;}
		GameControl_handler();
		virtual ~GameControl_handler();



		void Init();
		void Draw_Loading();
		void Draw_Characters(int selection);
		void Draw_Paused();
		void Draw_Playing();
		void Draw_End();

		void glShadowProjection(float *l, float * e, float * n); //funzione per renderizzare le ombre


		void DrawSky();



};


#endif /*GAMECONTROLHANDLER_H_*/
