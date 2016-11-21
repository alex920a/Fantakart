#include "Bomb.h"

void Bomb::Init()
{
	pz= 0;  //posizione provvisoria, da mettere random
	px= 0;


	angle_rot = 5; //lo faccio ruotare lungo l'asse z;
	jump_trasl=0.03;
	visible = true;
	lightOn = true;
	bomb = new Mesh((char*)"res/models/bomb.obj",0.8,0.8,0.8);
	grey = new Material(0.19225,0.19225,0.19225,0.50754,0.50754,0.50754,0.508273,0.508273,0.508273,0,0,0);




}

Bomb::Bomb()
{
	Init();
}

Bomb::~Bomb()
{

}

void Bomb::Render()
{

	glDisable(GL_TEXTURE_2D);

	DoStep();   //calcolo nuova rotazione della bomba

	glPushMatrix();
	if(lightOn)
		{
			glEnable(GL_LIGHTING);
			grey->active();
		}

		else
			glDisable(GL_LIGHTING);



		if(shadowOn)
			  glDisable(GL_LIGHTING);

	glTranslatef(px,py,pz);
    glRotatef(angle_rot, 0,1,0);  //ruoto il cubo
    glScalef(0.8,0.8,0.8);

    bomb->Render();

    glPopMatrix();


}

void Bomb::DoStep()
{

	//ad ogni step faccio ruotare la bomba

	angle_rot+=10;

}
