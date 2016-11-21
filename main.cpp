#include <math.h>
#include <string>
#include <sstream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


#include "Utils/Defines.h"
#include "Utils/GLText.h"
#include "GameControl_handler.h"
#include "Texture_handler.h"
#include "CameraHandler.h"
#include "Sound_handler.h"
#include "Light_handler.h"


using std::string;
using std::stringstream;


SDL_Window *win;
SDL_GLContext mainContext;
Uint32 windowID;
SDL_Joystick *joystick;

//FPS
Uint32 timeLastInterval=0;
float fps=0; //valore di fps nell'intervallo precedente
int fpsNow =0; //quanti fotogrammi ho disegnare fin'ora nell'intervallo attuale
unsigned int nstep= 0; //numero di passi di fisica fatti fin'ora


//mapping dei tasti della tastiera
static int keymap[Controller::NKEYS] = {SDLK_a, SDLK_d, SDLK_w, SDLK_s};


GameStatus gameStatus;  //game status
TTF_Font *font;
GLText* timer_text;



std::string programName = "FantaKart";


/* FUNCTIONS */

bool Init();
void CheckSDLError(int line);
bool SetOpenGLAttributes();
int Display_SetViewport(int width, int height);
void Cleanup();
void RunGame();

/* ******************************/


/* PHASES handler */
void Loading_handler();
void CharSelection_handler();
void Playing_handler();
void Pause_handler();
void End_handler();
/* ******************************/



int main(int argc, char* argv[])
{

	  if(!Init())
	  {
		  std::cout << "Error initializing the system!\n";
		  return -1;
	  }

	  	glClearColor(1, 1, 1, 0);
	  	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	  	SDL_GL_SwapWindow(win);   //schermata bianca


	  //attivo gestore gioco
	  gameStatus.ch = new GameControl_handler(&gameStatus);
	  gameStatus.ch ->Init();

	  //carico textures
	  gameStatus.th = new Texture_handler(&gameStatus);
	  gameStatus.th -> Init();
	  gameStatus.th ->printVectors(); //stampa il vettore contenente le texture caricate

	  //carico audio
	  gameStatus.sh = new Sound_handler(&gameStatus);
	  gameStatus.sh -> Init();
	  gameStatus.sh->printSoundsInfo(); //stampa quante canzoni sono state caricate

	  //carico camera
	  gameStatus.camera = new CameraHandler(&gameStatus);
	  gameStatus.camera->Init();


	  //carico luci
	  gameStatus.lh = new Light_handler(&gameStatus);
	  gameStatus.lh->Init();




	  //loop macchina stati finiti
	  RunGame();


	  //chiudiamo tutto
	  Cleanup();
	return (0);
}



void RunGame()
{
	//macchina a stati finiti
	bool done=false;

	while(!done)
	{

		switch(gameStatus.actualState)
		{
			case LOADING: //Loading
				Loading_handler();
				break;
			case CHARACTERS:
				CharSelection_handler();
				break;

			case PLAYING: //playing
				Playing_handler();
				break;

			case PAUSE: //pause
				Pause_handler();
				break;

			case END: // end
				End_handler();
				break;

			case QUIT: //quit game
				done = true;

				break;

		}

	}

}


void Loading_handler()
{

	bool loop = true;
	gameStatus.lh->state = true;
	gameStatus.lh->gouraud = true;
	glClearColor(1,1,1,0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//disegno la schermata di inizio
	gameStatus.LoadNewGame(); //carico nuovo gioco
	gameStatus.ch->Draw_Loading();  //render della schermata principale
	gameStatus.sh->LoadSong(0);  //partiamo con la musica di intro
	gameStatus.camera->Init();

	glFinish();
    SDL_GL_SwapWindow(win); //disegno


	while (loop)
	{
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN )
			{
				if(event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)
				{
					gameStatus.actualState = QUIT;
					loop = false;
				}
				else
				{
					gameStatus.actualState = CHARACTERS;
					loop = false;
				}

			}
		}
	}


}

void CharSelection_handler()
{

	glClearColor(0,0,0,0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	gameStatus.sh->LoadSong(3);
	gameStatus.ch->Draw_Characters(0); //parto dalla prima macchina
	glFinish();
	SDL_GL_SwapWindow(win); //disegno


	int selection = 0; //indice del personaggio

	bool loop = true;

		while (loop)
		{
			SDL_Event event;
			if (SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym)
						{
							case SDLK_KP_PLUS:
								selection++;  //seleziono il prossimo personaggio
								if(selection > NUM_MAX_CHARACTERS-1)
									selection= 0;
								break;

							case SDLK_KP_MINUS:
								selection--; //seleziono il personaggio precedente
								if(selection < 0)
									selection = NUM_MAX_CHARACTERS -1;
								break;

							case SDLK_RETURN:
								gameStatus.actualState = PLAYING;
								gameStatus.choosen_kart = selection;
								gameStatus.kart.Init(selection);
								loop = false;
								break;
						}
						break;


						case SDL_WINDOWEVENT:
						         // dobbiamo ridisegnare la finestra
						          if (event.window.event==SDL_WINDOWEVENT_EXPOSED)
						          {
						        	  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
						        	  gameStatus.ch->Draw_Characters(selection);
						        	  glFinish();
						        	  SDL_GL_SwapWindow(win); //disegno
						          }

						          else{
						           windowID = SDL_GetWindowID(win);
						           if (event.window.windowID == windowID)  {
						             switch (event.window.event)  {
						                  case SDL_WINDOWEVENT_SIZE_CHANGED:  {
						                    int  scrW = event.window.data1;
						                    int  scrH = event.window.data2;
						                     glViewport(0,0,scrW,scrH);
						                     gameStatus.ch->Draw_Characters(selection);
						                     glFinish();
						                     SDL_GL_SwapWindow(win); //disegno
						                     break;
						                  }
						             }
						            }
						          }
						  break;

					}//switch
			}
			else
			{
				// nessun evento: siamo IDLE

				      Uint32 timeNow=SDL_GetTicks(); // che ore sono?

				      bool doneSomething=false;
				      int guardia=0; // sicurezza da loop infinito

				      // finche' il tempo simulato e' rimasto indietro rispetto
				      // al tempo reale...
				      while (nstep*PHYS_SAMPLING_STEP < timeNow ) {
				        nstep++;
				        doneSomething=true;
				        timeNow=SDL_GetTicks();
				        if (guardia++>1000) {loop=false; break;} // siamo troppo lenti!
				      }

				      if (doneSomething)
				      {
				    	  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				    	  gameStatus.ch->Draw_Characters(selection);
						  glFinish();
						  SDL_GL_SwapWindow(win); //disegno
				      }
			}
		} //loop


}


void Playing_handler()
{

	glClearColor(0,0,0,0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	gameStatus.camera->SetCamera();
	gameStatus.sh->LoadSong(1);

	gameStatus.ch->Draw_Playing();
	glFinish();
	SDL_GL_SwapWindow(win); //disegno



	gameStatus.gameTime.LoadNewTime();  //reset del timer di gioco

	bool loop = true;


	while (loop)
	{
		SDL_Event event;

		//controllo subito il tempo: se è finito termino la partita
		gameStatus.gameTime.ComputeNewTime();


		if(gameStatus.gameTime.TimerEnded() )
		{
			gameStatus.actualState = END;  //ci portiamo allo stato di end se è finito il tempo
			break;
		}

		if(gameStatus.score == NUM_MAX_CRYSTALS)
		{

			gameStatus.actualState = END;  //ci portiamo allo stato di end se si sono raccolti tutti i cristalli
			gameStatus.losing = false;
			break;
		}


		if (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
					case SDL_KEYDOWN:
						gameStatus.kart.controller.EatKey(event.key.keysym.sym, keymap,true);

						switch (event.key.keysym.sym)
						{
							case SDLK_p:
								//pause the game
								gameStatus.actualState = PAUSE;
								loop = false;
								break;
							//visuali della camera
							case SDLK_F1:
								gameStatus.camera->SetPOVCamera((gameStatus.camera->camera_state + 1) % CAMERA_TYPE_MAX);

								break;
							case SDLK_F2: //attivo/ disattivo le luci
								gameStatus.lh->state = ! gameStatus.lh->state;
								break;
							case SDLK_F3: //modalità shading flat o gouraud
								gameStatus.lh->gouraud = ! gameStatus.lh->gouraud;
								break;


						}
						break;
					case SDL_KEYUP:
						gameStatus.kart.controller.EatKey(event.key.keysym.sym, keymap,false);
						break;

					case SDL_WINDOWEVENT:
					         // dobbiamo ridisegnare la finestra
					          if (event.window.event==SDL_WINDOWEVENT_EXPOSED)
					          {
					        	  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
					        	  gameStatus.camera->SetCamera();

					        	  gameStatus.ch->Draw_Playing();
					        	  glFinish();
					        	  SDL_GL_SwapWindow(win); //disegno
					          }

					          else{
					           windowID = SDL_GetWindowID(win);
					           if (event.window.windowID == windowID)  {
					             switch (event.window.event)  {
					                  case SDL_WINDOWEVENT_SIZE_CHANGED:  {
					                    int  scrW = event.window.data1;
					                    int  scrH = event.window.data2;
					                     glViewport(0,0,scrW,scrH);
					                     gameStatus.camera->SetCamera();
					                     gameStatus.ch->Draw_Playing();
					                     glFinish();
					                     SDL_GL_SwapWindow(win); //disegno
					                     break;
					                  }
					             }
					            }
					          }
					  break;



					case SDL_MOUSEWHEEL:
					       if (event.wheel.y < 0 ) {
					         // avvicino il punto di vista (zoom in)
					    	   gameStatus.camera->camera_distance*=0.9;
					         //if (gameStatus.camera->camera_distance<3) gameStatus.camera->camera_distance = 3;
					       };
					       if (event.wheel.y > 0 ) {
					         // allontano il punto di vista (zoom out)
					    	   gameStatus.camera->camera_distance/=0.9;
					       };
					     break;
//					case SDL_MOUSEMOTION: //per debug
//					        if (event.motion.state & SDL_BUTTON(1) ) {
//					        	gameStatus.camera->cam_angle[1]+=event.motion.xrel;
//					        	gameStatus.camera->cam_angle[0] +=event.motion.yrel;
//
////					          if (gameStatus.camera->cam_angle[0]<+5) gameStatus.camera->cam_angle[0]=+5; //per non andare sotto la macchina
////					          if (gameStatus.camera->cam_angle[0]>+90) gameStatus.camera->cam_angle[0]=+90;
//
//					        }
//					        break;
			}

		}
		else
		{
			// nessun evento: siamo IDLE

			      Uint32 timeNow=SDL_GetTicks(); // che ore sono?

			      if (timeLastInterval+FPS_SAMPLING<timeNow) {
			        // e' tempo di ricalcolare i Frame per Sec
			        fps = 1000.0*((float)fpsNow) /(timeNow-timeLastInterval);
			        std::cout<<"FPS: "<<fps<<std::endl;
			        fpsNow=0;
			        timeLastInterval = timeNow;
			      }

			      bool doneSomething=false;
			      int guardia=0; // sicurezza da loop infinito

			      // finche' il tempo simulato e' rimasto indietro rispetto
			      // al tempo reale...
			      while (nstep*PHYS_SAMPLING_STEP < timeNow ) {
			    	if(!gameStatus.kart.stopActive)
			    		gameStatus.kart.DoStep();
			    	else
			    	{
			    		gameStatus.kart.timeStop.ComputeNewTime();
			    		if(gameStatus.kart.timeStop.TimerEnded())
			    			gameStatus.kart.stopActive = false;
			    	}

			        nstep++;
			        doneSomething=true;
			        timeNow=SDL_GetTicks();
			        if (guardia++>1000) {loop=false; break;} // siamo troppo lenti!
			      }

			      if (doneSomething)
			      {
			    	  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			    	  gameStatus.camera->SetCamera();
			    	  gameStatus.DetectCollisionKart();
			    	  fpsNow++;
			    	  gameStatus.ch->Draw_Playing();
					  glFinish();
					  SDL_GL_SwapWindow(win); //disegno
			      }

		}
	} //loop

}

void Pause_handler()
{

	glClearColor(1,1,1,0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	gameStatus.sh->StopSong();
	gameStatus.sh->PlayEffect(0);
	gameStatus.ch->Draw_Paused();
	glFinish();
	SDL_GL_SwapWindow(win); //disegno


	bool loop = true;

	while (loop)
	{
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{

				case SDLK_r: //ripresa del gioco
					gameStatus.actualState = PLAYING;
					loop = false;
					break;
				case SDLK_q: //uscita dal gioco
					gameStatus.actualState = QUIT;
					loop = false;
					break;

				case SDLK_n: //nuovo gioco
					gameStatus.actualState = LOADING;
					loop = false;
					break;
				}
			}
		}
	} //loop
}

void End_handler()
{

	glClearColor(1,1,1,0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	gameStatus.sh->LoadSong(2);
	gameStatus.ch->Draw_End();
	glFinish();
	SDL_GL_SwapWindow(win); //disegno

	bool loop = true;

	while (loop)
	{
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_n: //nuovo gioco
					gameStatus.actualState = LOADING;
					loop = false;
					break;
				case SDLK_q: //chiudo il gioco
					gameStatus.actualState = QUIT;
					loop = false;
					break;

				}
			}
		}
	} //loop
}


int Display_SetViewport(int width, int height)
{
	/* Height / width rapporto */
	    GLfloat ratio;

	    /* Protect against a divide by zero */
	    if ( height == 0 ) {
	        height = 1;
	    }

	    ratio = ( GLfloat )width / ( GLfloat )height;

	    /* Setup viewport. */
	    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

	    /* settiamo la matrice di proiezione. */
	    glMatrixMode( GL_PROJECTION );
	    glLoadIdentity( );

	    /* prospettiva */
	    gluPerspective( 90.0f, ratio, 1.0f, 1000.0f );

	    /* Make sure we're changing the model view and not the projection */
	    glMatrixMode( GL_MODELVIEW );
	    glLoadIdentity();

	    return 1;

}








void CheckSDLError(int line = -1)
{
	std::string error = SDL_GetError();

	if (error != "")
	{
		std::cout << "SLD Error : " << error << std::endl;

		if (line != -1)
			std::cout << "\nLine : " << line << std::endl;

		SDL_ClearError();
	}
}


void Cleanup()
{
	// Delete our OpengL context
		SDL_GL_DeleteContext(mainContext);

		// Destroy our window
		SDL_DestroyWindow(win);

		//chiudere interfacce SDL?

		// Shutdown SDL 2
		SDL_Quit();
}


bool Init()
{
	 // inizializzazione di SDL
		  if(SDL_Init( SDL_INIT_VIDEO ) < 0)
		  {
			  std::cout <<"Failed to init SDL\n";
			  return false;
		  }

		  if(SDL_Init( SDL_INIT_AUDIO ) < 0)
		  {
			  std::cout <<"Failed to init SDL audio\n";
			  return false;
		  }
		  if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) == -1)
		  {
			  std::cout <<"Failed to open mix open audio\n";
			  return false;
		  }

		  if (TTF_Init () < 0)
		  {
			  fprintf (stderr, "Couldn't initialize TTF: %s\n", SDL_GetError ());
			  SDL_Quit ();
			  return (2);
		  }


		  //creo window centrata
		  win=SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				  SCR_W, SCR_H, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

		  if(!win)
		  {
			  std::cout <<"Unable to create main window\n";
			  CheckSDLError(__LINE__);
			  return false;
		  }

		  //Create our opengl context and attach it to our window
		  mainContext=SDL_GL_CreateContext(win);

		  //settiamo gli attributi OpenGL
		  SetOpenGLAttributes();

		  // This makes our buffer swap syncronized with the monitor's vertical refresh
		  SDL_GL_SetSwapInterval(1);


		  Display_SetViewport(SCR_W,SCR_H);

		  return true;
}


bool SetOpenGLAttributes()
{
	// Set our OpenGL version.
		// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

		// Turn on double buffering with a 24bit Z buffer.
		// You may need to change this to 16 or 32 for your system
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //correzione prospettica

		glEnable(GL_DEPTH_TEST); //abilito zbuffer


		return true;
}






