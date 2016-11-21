#include "Speedometer.h"

Speedometer::Speedometer()
{
	this->rect_center_x = 0.0f;
	this->rect_center_y = 0.0f;
	this->h = this->w = 0.0f;
	this->speed_list = 0;
	this->arrow_y_reset = 0;
	this->arrow_w = 0;
	this->arrow_h = 0;
	this->arrow_center_x = this->arrow_center_y = 0;
}

Speedometer::Speedometer(float cx,float cy, float h, float w)
{
	this->rect_center_x = cx;
	this->rect_center_y = cy;
	this->w = w;
	this->h = h;
	this->speed_list = 0;
	this->arrow_y_reset = 0;
	this->arrow_w = 0;
	this->arrow_h = 0;
	this->arrow_center_x = this->arrow_center_y = 0;
}

void Speedometer::Init()
{
	speed_list = glGenLists(2);

	this->rect_center_x = SCR_W - 30 ;
	this->rect_center_y = 140;
	this->w = 60;
	this->h = this->rect_center_y*2;
	arrow_h = arrow_w= 40;

	this->arrow_center_x = rect_center_x -  this->w ;
	this->arrow_center_y = arrow_y_reset= rect_center_y- h/2.0f+ arrow_h/2.0f;



    float x1 = rect_center_x-w/2.0f;
    float y1 = rect_center_y-h/2.0f;
    float x2 = rect_center_x+w/2.0f;
    float y2 = rect_center_y+h/2.0f;




	glNewList(speed_list,GL_COMPILE);
	glPushMatrix();                     //disegno le finestre di controllo
		   	  glDisable(GL_DEPTH_TEST);
		   	  glDisable(GL_LIGHTING);
		   	  glEnable(GL_TEXTURE_2D);

		   	  glColor3f(1,1,1);

		   	  SetCoordToPixel();

		   	   glBindTexture(GL_TEXTURE_2D, TEX_SPEEDOMETER);  //indicatore velocita
				glBegin(GL_POLYGON);
				glTexCoord2f(0, 1);
				glVertex2f(x1, y1);

				glTexCoord2f(1, 1);
				glVertex2f(x2, y1);

				glTexCoord2f(1, 0);
				glVertex2f(x2, y2);

				glTexCoord2f(0, 0);
				glVertex2f(x1, y2);
				glEnd();



		   	  glEnable(GL_DEPTH_TEST);



		   glPopMatrix();
	glEndList();



}

void Speedometer::DrawSpeedometer(float velModule)
{

	glCallList(speed_list);
	DrawArrow(velModule);
}

void Speedometer::DrawArrow(float velModule)
{
	//std::cout<<" vel:"<<velModule<<std::endl;
	this->arrow_center_y = arrow_y_reset;   //reset ad ogni giro

	float magic_number; //vel max.

	//posizione verticale della freccia calcolata con proporzione
	if(velModule > 0.15)
	{
		magic_number = 0.60f;
		arrow_center_y += (5.0f/6.0f)*h + ((1.0f/6.0f) * h * velModule) / magic_number -arrow_h/2.0f; //da modificare?
	}

	else
	{
		magic_number = 0.15f;
		arrow_center_y += (velModule* (5.0f/6.0f)*h) / magic_number;
	}




	float arrow_x1 = arrow_center_x-arrow_w/2.0f;
	float arrow_y1 = arrow_center_y-arrow_h/2.0f;
	float arrow_x2 = arrow_center_x+arrow_w/2.0f;
	float arrow_y2 = arrow_center_y+arrow_h/2.0f;




    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	  glDisable(GL_DEPTH_TEST);
	  glDisable(GL_LIGHTING);
	  glEnable(GL_TEXTURE_2D);

	  glColor3f(1,1,1);
	  SetCoordToPixel();
	glBindTexture(GL_TEXTURE_2D, TEX_ARROW);
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 0);
	glVertex2f(arrow_x1, arrow_y1);

	glTexCoord2f(0, 0);
	glVertex2f(arrow_x2,arrow_y1);

	glTexCoord2f(0, 1);
	glVertex2f(arrow_x2, arrow_y2);

	glTexCoord2f(1, 1);
	glVertex2f(arrow_x1, arrow_y2);
	glEnd();

 	  glEnable(GL_DEPTH_TEST);


   glPopMatrix();


}


