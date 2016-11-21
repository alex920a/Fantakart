#include "Hourglass.h"

void Hourglass::Init()
{
	pz= 0;  //posizione provvisoria, da mettere random
	px= 0;
	py = 0;


	visible = true;
	lightOn = true;
	hourglass = new Mesh((char*)"res/models/hourglass00.obj",0.5,0.5,0.5);
	bronze = new Material(0.11,0.06,0.11,1,0.75,0,0.33,0.33,0.52,0.32,0,0);



}

Hourglass::Hourglass()
{
	Init();
}

Hourglass::~Hourglass()
{

}

void Hourglass::Render()
{

	glDisable(GL_TEXTURE_2D);


	glPushMatrix();

	if(lightOn)
		{
			glEnable(GL_LIGHTING);
			bronze->active();
		}

		else
			glDisable(GL_LIGHTING);



		if(shadowOn)
			  glDisable(GL_LIGHTING);


	glTranslatef(px,py,pz);     //traslo in verticale su e giu
    glScalef(0.5,0.5,0.5);

    hourglass->Render();

    glPopMatrix();

}


