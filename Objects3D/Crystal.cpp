#include "Crystal.h"

void Crystal::Init()
{
	pz= 0;  //posizione provvisoria, da mettere random
	px= 0;
	py= 0;

	angle_rot = 5; //lo faccio ruotare lungo l'asse z;
	jump_trasl=0.03;
	visible = true;
	crystal = new Mesh((char*)"res/models/exp-crystal.obj", 0.2f,0.2f,0.2f);
	emerald= new Material(0.0215, 0.1745, 0.0215, 0.07568, 0.61424, 0.07568, 0.633, 0.727811, 0.633,0,0,0);




}

Crystal::Crystal()
{
	Init();
}

Crystal::~Crystal()
{

}

void Crystal::Render()
{



	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);




	DoStep();   //calcolo nuova posizione e rotazione del cubo

	glPushMatrix();

	if(lightOn)
	{
		glEnable(GL_LIGHTING);
		emerald->active();
	}

	else
		glDisable(GL_LIGHTING);



	if(shadowOn)
		  glDisable(GL_LIGHTING);



	glTranslatef(px,py,pz);     //traslo in verticale su e giu
    glRotatef(angle_rot, 0,1,0);  //ruoto il cubo



    glScalef(0.2,0.2,0.2);

    crystal->Render();

    glPopMatrix();


}

void Crystal::DoStep()
{

	//ad ogni step faccio ruotare il cubo e lo traslo su e giu
	py+=jump_trasl;
	if(py> 0.5)
		jump_trasl= -jump_trasl;
	else if(py< 0)
		jump_trasl= -jump_trasl;

	angle_rot++;

}
