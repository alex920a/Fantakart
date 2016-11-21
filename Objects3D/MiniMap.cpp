#include "MiniMap.h"



const float DEG2RAD = 3.14159/180;


MiniMap::MiniMap()
{
	map_list_name = 0;


}



void MiniMap::Init()
{
	map_list_name = glGenLists(1); //display list



	glNewList(map_list_name,GL_COMPILE);
	glPushMatrix();                     //disegno le finestre di controllo
		   	  glDisable(GL_DEPTH_TEST);
		   	  glDisable(GL_LIGHTING);
		   	  glEnable(GL_TEXTURE_2D);
		   	  glBindTexture(GL_TEXTURE_2D, TEX_MAP_GRID);
		   	  glEnable(GL_BLEND);
		   	  SetCoordToPixel();
		   	  glColor3f(1,1,1);
		   	  DrawCircle(SCR_W-80,SCR_H-80,80,40);  //mappa
		   	  glDisable(GL_TEXTURE_2D);
		   	  glColor3f(1,0,0); //disegno la macchina come un puntino rosso
		   	  DrawCircle(SCR_W-80,SCR_H-80,10,40);
		   	  glEnable(GL_DEPTH_TEST);
		   	  glDisable(GL_BLEND);
		   glPopMatrix();
	glEndList();
}



void MiniMap::DrawMap()
{
	glCallList(map_list_name);

}

void MiniMap::DrawElement(float cx, float cy,float px,float py,int type_object)
{
	switch(type_object)
	{
		case 0: //crystal
			glColor3f(0,0.5,0.5);
			break;
		case 1: // bombs
			glColor3f(0.8,0.5,0);
			break;

		case 2: //hourglass
			glColor3f(1,1,1);
			break;
	}

	glPushMatrix();
				glDisable(GL_DEPTH_TEST);
			    glDisable(GL_LIGHTING);
			    glDisable(GL_TEXTURE_2D);
			    SetCoordToPixel();

			    if(!(abs(px-cx) *5 >=50 || abs(py-cy) *5 >=50))  //range di visibilità nella minimappa
			    	DrawCircle(SCR_W-80+(px-cx)*5 ,( SCR_H-80+(py-cy)*5 ), 5, 40);
				glEnable(GL_DEPTH_TEST);
	glPopMatrix();

}
