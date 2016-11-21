#include "PhotoId.h"


const float DEG2RAD = 3.14159/180;


PhotoId::PhotoId()
{
	foto_list_name = 0;
}



void PhotoId::Init()
{
	foto_list_name = glGenLists(1); //display list



	glNewList(foto_list_name,GL_COMPILE);
	glPushMatrix();
		   	  glDisable(GL_DEPTH_TEST);
		   	  glDisable(GL_LIGHTING);
		   	  glEnable(GL_TEXTURE_2D);
		   	  glBindTexture(GL_TEXTURE_2D, TEX_PHOTO);
		   	  glColor3f(1,1,1);
		   	  SetCoordToPixel();
		   	  DrawCircle(60,60,60,40);
		   	  glEnable(GL_DEPTH_TEST);


		   glPopMatrix();
	glEndList();


}



void PhotoId::DrawPhoto()
{
	glBindTexture(GL_TEXTURE_2D, 8);
	glCallList(foto_list_name);

}
