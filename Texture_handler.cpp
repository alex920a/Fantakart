#include "Texture_handler.h"

using namespace std;

Texture_handler::~Texture_handler(){}



void Texture_handler::Init()
{
	//textures loading


	LoadTexture(TEX_PAUSE,(char*)PAUSE_SCREEN.c_str());
	LoadTexture(TEX_MAIN,(char*)MAIN_SCREEN.c_str());
	LoadTexture(TEX_ROAD,(char*)ROAD.c_str());
	LoadTexture(TEX_CRASH,(char*)CRASH_KART.c_str());
	LoadTexture(TEX_END_LOSE,(char*)END_SCREEN_LOSE.c_str());
	LoadTexture(TEX_END_WIN,(char*)END_SCREEN_WIN.c_str());
	LoadTexture(TEX_SKY,(char*)SKY_TEX.c_str());
	LoadTexture(TEX_PHOTO,(char*)MYPHOTO.c_str());
	LoadTexture(TEX_CORTEX,(char*)CORTEX_KART.c_str());
	LoadTexture(TEX_SPEEDOMETER,(char*)SPEEDOMETER.c_str());
	LoadTexture(TEX_ARROW,(char*)ARROW.c_str());
	LoadTexture(TEX_OXIDE,(char*)OXIDE_KART.c_str());
	LoadTexture(TEX_MAP_GRID,(char*)MAP_GRID.c_str());
	LoadTexture(TEX_CORTEX_BODY,(char*)CORTEX_BODY.c_str());
	LoadTexture(TEX_CRASH_BODY,(char*)CRASH_BODY.c_str());
	LoadTexture(TEX_OXIDE_BODY,(char*)OXIDE_BODY.c_str());
	LoadTexture(TEX_HOLE,(char*)HOLE.c_str());
	LoadTexture(TEX_WALL,(char*)WALL.c_str());
	LoadTexture(TEX_CHESS, (char*)CHESS.c_str());


}

bool Texture_handler::LoadTexture(int textbind, char *filename){
  SDL_Surface *s = IMG_Load(filename);
  if (!s) return false;

	  glBindTexture(GL_TEXTURE_2D, textbind);
	  gluBuild2DMipmaps(
		GL_TEXTURE_2D,
		GL_RGB,
		s->w, s->h,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		s->pixels
	  );
	  glTexParameteri(
	  GL_TEXTURE_2D,
	  GL_TEXTURE_MAG_FILTER,
	  GL_LINEAR );
	  glTexParameteri(
	  GL_TEXTURE_2D,
	  GL_TEXTURE_MIN_FILTER,
	  GL_LINEAR_MIPMAP_LINEAR );

	   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
	   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	  //store in vectors
	  texs.push_back(filename);
	  texNames.push_back(textbind);

	  return true;
}

void Texture_handler::printVectors()
{
	cout << "Texs loaded:"<<endl;

	for (unsigned int i = 0; i < texs.size(); i++)
	    cout << texs.at(i) << " \n ";
	cout<<endl<<endl;


}


