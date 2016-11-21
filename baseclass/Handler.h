#ifndef HANDLER_H_
#define HANDLER_H_

#include "GameStatus.h"
#include "../Utils/Defines.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <vector>



class Handler  //superclasse per i vari handler
{
	protected:
		GameStatus* state;


	public:

		Handler(){ state = NULL; }
		Handler(GameStatus* g ){ state = g;}

		void SetState(GameStatus* g){ state = g;}
		GameStatus* getState(){ return state;}



		virtual void Init(){}
		virtual ~Handler();
};


#endif /*HANDLER_H_*/
