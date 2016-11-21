#ifndef TEXTUREHANDLER_H_
#define TEXTUREHANDLER_H_

#include "baseclass/Handler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>

class Texture_handler : public Handler
{
	public:
		std::vector<int> texNames;
		std::vector< char*> texs;

		Texture_handler(): Handler(){}
		Texture_handler(GameStatus* g): Handler(g){};

		void Init();
		//altri metodi

		virtual ~Texture_handler();
		bool LoadTexture(int textbind,char *filename);
		void printVectors();

};

#endif /*TEXTUREHANDLER_H_*/
