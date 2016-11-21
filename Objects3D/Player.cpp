#include "Player.h"

void Player::Init(int selection)
{
	pz=0;  //posizione provvisoria,
	px= 0;
	py= 0;




	switch(selection)
	{
	case 0 : //oxide
		player = new Mesh((char*)"res/models/Oxide/Oxide.obj");
				break;
	case 1 : //crash
		player = new Mesh((char*)"res/models/Crash/Crash.obj");
		break;
	case 2 : //cortex
			player = new Mesh((char*)"res/models/Cortex/cortex.obj");
			break;
	}


}

Player::Player(int selection)
{
	Init(selection);
}

Player::~Player()
{

}

void Player::Render(int selection)
{
	//riabilito il light
	glDisable(GL_LIGHTING);  //nelle schermate NON di gioco, viene disabilitato il lightining.
				 	 	 	 	 	 	 //In fase di playing occorre riabilitarlo
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);


	glPushMatrix();


    glColor3f(1,1,1);

    glScalef(0.1,0.1,0.1);

    switch(selection)
   	  {
   	  	  	case 0:
   		  	  	  	  	glBindTexture(GL_TEXTURE_2D, TEX_OXIDE_BODY);
   		  	  			break;
   	  	  	case 1:
   						glBindTexture(GL_TEXTURE_2D, TEX_CRASH_BODY);
   						break;
   	  	  	case 2:
   						glBindTexture(GL_TEXTURE_2D, TEX_CORTEX_BODY);
   						break;

   	  }

    player->Render();

    glPopMatrix();


}


