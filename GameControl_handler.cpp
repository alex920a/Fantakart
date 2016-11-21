#include "GameControl_handler.h"


GameControl_handler::GameControl_handler(){screen_name = chess_list= 0;font = NULL;}
GameControl_handler::~GameControl_handler(){}


const float radius = 1;
const float DEG2RAD = 3.14159/180;
const float dimx=10;
const float dimy=10;



void GameControl_handler::Init()
{

	screen_name = glGenLists(1);    //display list per i menu

	glNewList(screen_name,GL_COMPILE);

	glBegin(GL_QUADS);
	        glColor3f( 1.0f, 1.0f, 1.0f);
	              glTexCoord2f(0.0f, 0.0f);
	              glVertex2d(0,SCR_H);

	              glTexCoord2f(0.0f, 1.0f);
	              glVertex2d(0,0);

	              glTexCoord2f(1.0f, 1.0f);
	              glVertex2d(SCR_W,0);

	              glTexCoord2f(1.0f, 0.0f);
	              glVertex2d(SCR_W,SCR_H);
	 glEnd();

	glEndList();

	float K=4;
   chess_list = glGenLists(1);   //display list per il floor della schermata dei personaggi
   glNewList(chess_list, GL_COMPILE);
   glBindTexture(GL_TEXTURE_2D,TEX_CHESS);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glBegin(GL_QUADS);
   		     glColor3f(1, 1, 1); // colore uguale x tutti i quads
   		     glNormal3f(0,1,0);       // normale verticale uguale x tutti
   		     for (int x=0; x<K; x++)
   		     for (int z=0; z<K; z++) {
   		       float x0=-S_FLOOR_SIZE + 2*(x+0)*S_FLOOR_SIZE/K;
   		       float x1=-S_FLOOR_SIZE + 2*(x+1)*S_FLOOR_SIZE/K;
   		       float z0=-S_FLOOR_SIZE + 2*(z+0)*S_FLOOR_SIZE/K;
   		       float z1=-S_FLOOR_SIZE + 2*(z+1)*S_FLOOR_SIZE/K;

   		       glTexCoord2f(0,0);
   		       glVertex3d(x0, 0, z0);
   		       glTexCoord2f(1,0);
   		       glVertex3d(x1, 0, z0);
   		       glTexCoord2f(1,1);
   		       glVertex3d(x1, 0, z1);
   		       glTexCoord2f(0,1);
   		       glVertex3d(x0, 0, z1);
   		     }
   		   glEnd();

   	glEndList();




	  //inizializzo anche la libreria ttf
	  font = TTF_OpenFont ("neuropol.ttf", DEFAULT_PTSIZE);
	 // font = TTF_OpenFont ("/Library/Fonts/Arial.ttf", DEFAULT_PTSIZE);

	  if (font == NULL)
	  {
		  fprintf (stderr, "Couldn't load font\n");
	  }




}





void GameControl_handler::Draw_Loading()
{
	 glEnable(GL_TEXTURE_2D);
	 SetCoordToPixel();
	 glBindTexture(GL_TEXTURE_2D,TEX_MAIN);
	 glDisable(GL_LIGHTING);   //disabilito momentaneamente le luci in modo che non abbiamo dei riflessi non voluti
	 glCallList(screen_name);


}

void GameControl_handler::Draw_Characters(int selection)
{

	state->camera->SetCamera();

	glLoadIdentity();
	gluLookAt(-6+6*selection,3,3,-6+6*selection,0,0,0,1,0); //permette di spostare la camera in base alla selezione


	for(int i = 0; i<NUM_MAX_CHARACTERS;i++)
	{
		//renderizziamo i kart
		glPushMatrix();
			glTranslatef(-6+6*i,0,0);
			glRotatef(180,0,1,0);

			Kart kart;
			kart.Init(i);   //nel menu di selezione del personaggio si creano NUM_MAX_CHARACTERS
			kart.Render(i);
		glPopMatrix();


		//renderizziamo i player
		glPushMatrix();
			glTranslatef(-6+6*i,0,-2);
			Player player(i);
			player.Render(i);
		glPopMatrix();
	}

	glEnable(GL_TEXTURE_2D);

	//disegnamo il floor dei player
	glCallList(chess_list);


}


void GameControl_handler::Draw_Paused()
{
	 glDisable(GL_DEPTH_TEST);
     glDisable(GL_LIGHTING);
     SetCoordToPixel();
	 glBindTexture(GL_TEXTURE_2D,TEX_PAUSE);
	 glEnable(GL_TEXTURE_2D);
	 glColor3f(1,1,1); // metto il colore neutro (viene moltiplicato col colore texture, componente per componente)
	 glCallList(screen_name);

}

void GameControl_handler::Draw_Playing()
{
	//variabili per ombre
	float l[3] ; // Coordinate della sorgente luminosa
	float n[] = { 0.0,  -1.0, 0.0 }; // vettore normale per il piano su cui si proiettano le ombre
	float e[] = { 0.0, 0.05, 0.0 }; // Point of the plane




	if(state->lh->state) //luce attiva
	{
		 state->lh->SetPositionLight(20,20,20);

		 l[0] = state->lh->posizione_luce[0];
		 l[1] = state->lh->posizione_luce[1];
		 l[2] = state->lh->posizione_luce[2];
		 glEnable(GL_LIGHTING);
	}
	else
		glDisable(GL_LIGHTING); //disattiviamo le luci


	//disegno il cielo
	   DrawSky();

	   //disegno il mondo (no light)
       state->world.Render();

       //disegno i kart
       state->kart.shadowOn = false;
	   state->kart.Render(state->choosen_kart);

	   if(state->lh->state  )
	   {
		   //se è attiva la luce abilito il LIGHTING e le ombre
		   glPushMatrix();
		   glShadowProjection(l,e,n);
		   glDisable(GL_LIGHTING);
		   glColor3f(0.3,0.3,0.3); //colore dell'ombra

		   state->kart.shadowOn = true;
		   state->kart.Render(state->choosen_kart);
		   glPopMatrix();
	   }



	   glDisable(GL_LIGHTING);
	   glEnable(GL_LIGHTING); //hack
	   //disegno i cristalli
	   int i;
	   for(i=0 ; i < NUM_MAX_CRYSTALS;i++)
		   if(state->crystals.at(i).visible)  //se lo stato del cristallo è "visible" allora lo renderizzo
		   {
			   state->crystals.at(i).lightOn = state->lh->state;
			   state->crystals.at(i).shadowOn = false; //spengo le ombre per l'oggetto reale

			   if(state->lh->gouraud)  //gouraud shading altrimenti flat
				   state->crystals.at(i).crystal->gouraud = true;
			   else
				   state->crystals.at(i).crystal->gouraud = false;

			   state->crystals.at(i).Render();

			   if(state->lh->state )
			   {
				   //se è attiva la luce abilito il LIGHTING e le ombre
				   glPushMatrix();
				   glShadowProjection(l,e,n);
				   glDisable(GL_LIGHTING);
				   glColor3f(0.3,0.3,0.3); //colore dell'ombra

				   state->crystals.at(i).shadowOn = true;
				   state->crystals.at(i).Render();
				   glEnable(GL_LIGHTING);
				   glPopMatrix();
			   }

		   }


	   glDisable(GL_LIGHTING);
	   glEnable(GL_LIGHTING); //hack
	   //disegno le clessidre
	   for(i=0 ; i < NUM_MAX_HOURGLASSES;i++)
	   		   if(state->hourglasses.at(i).visible)  //se lo stato del cubo è "visible" allora lo disegnamo
	   		   {
	   			   state->hourglasses.at(i).lightOn = state->lh->state;
	   			   state->hourglasses.at(i).shadowOn = false;

	   			if(state->lh->gouraud)  //gouraud shading altrimenti flat
				   state->hourglasses.at(i).hourglass->gouraud = true;
			   else
				   state->hourglasses.at(i).hourglass->gouraud = false;

	   			   state->hourglasses.at(i).Render();

	   			 if(state->lh->state)
	   			 {
	   				//se è attiva la luce abilito il LIGHTING e le ombre
					   glPushMatrix();
					   glShadowProjection(l,e,n);
					   glDisable(GL_LIGHTING);
					   glColor3f(0.3,0.3,0.3); //colore dell'ombra

					   state->hourglasses.at(i).shadowOn = true;
					   state->hourglasses.at(i).Render();
					   glEnable(GL_LIGHTING);
					   glPopMatrix();
	   			 }
	   		   }


	   glDisable(GL_LIGHTING);
	   glEnable(GL_LIGHTING); //hack
	   //disegno le bombe
	   for(i=0 ; i < NUM_MAX_BOMBS;i++)
	   	   		   if(state->bombs.at(i).visible)  //se lo stato del cubo è "visible" allora lo disegnamo
	   	   		   {
	   	   			   state->bombs.at(i).lightOn = state->lh->state;
	   	   			   state->bombs.at(i).shadowOn = false;

	   	   			   if(state->lh->gouraud)  //gouraud shading altrimenti flat
						   state->bombs.at(i).bomb->gouraud = true;
					   else
						   state->bombs.at(i).bomb->gouraud = false;

	   	   			   state->bombs.at(i).Render();

	   	   			   if(state->lh->state )
	   	   			   {
	   	   				  //se è attiva la luce abilito il LIGHTING e le ombre
						   glPushMatrix();
						   glShadowProjection(l,e,n);
						   glDisable(GL_LIGHTING);
						   glColor3f(0.3,0.3,0.3); //colore dell'ombra
						   state->bombs.at(i).shadowOn = true;
						   state->bombs.at(i).Render();
						   glEnable(GL_LIGHTING);
						   glPopMatrix();
	   	   			   }
	   	   		   }



	   //disegno la mia foto
	   state->myPhoto.DrawPhoto();
	   //disegno la minimappa
	   state->miniMap.DrawMap();
	   //disegno l'indicatore di velocità
       state->speedometer.DrawSpeedometer(state->kart.velModule);




       	 //disegno elementi nella minimappa
	   for(int i=0;i<NUM_MAX_CRYSTALS;i++)
		   if(state->crystals.at(i).visible)
			   state->miniMap.DrawElement(state->crystals.at(i).px,state->crystals.at(i).pz,state->kart.px, state->kart.pz, 0);

	   for(int i=0;i<NUM_MAX_BOMBS;i++)
	   		   if(state->bombs.at(i).visible)
	   			   state->miniMap.DrawElement(state->bombs.at(i).px,state->bombs.at(i).pz,state->kart.px, state->kart.pz, 1);

	   for(int i=0;i<NUM_MAX_HOURGLASSES;i++)
	   		   if(state->hourglasses.at(i).visible)
	   			   state->miniMap.DrawElement(state->hourglasses.at(i).px,state->hourglasses.at(i).pz,state->kart.px, state->kart.pz, 2);




	   //disegno le scritte del timer e dei cristalli rimasti
	   SetCoordToPixel();
	   GLText* timer_text = new GLText(TEXT_TIMER,font);
	   char buffer[40];
	   sprintf(buffer, "Tempo rimasto: %d secondi",state->gameTime.time_left);
		timer_text-> setText(buffer, 0,255,255);
		timer_text-> setPosition(0,SCR_H);
		timer_text->render();

	   GLText* score_text = new GLText(TEXT_SCORE,font);
	   char buffer_score[40];
	   sprintf(buffer_score,"Cristalli rimasti: %d", state->crystals.size()- state-> score);
	   score_text->setText(buffer_score, 255,255,0);
	   score_text->setPosition(0,SCR_H-DEFAULT_PTSIZE-15);
	   score_text->render();


	   glEnable(GL_DEPTH_TEST);
	   glEnable(GL_LIGHTING);


}

void GameControl_handler::Draw_End()
{
		SetCoordToPixel();

		 if(state->losing)
			 glBindTexture(GL_TEXTURE_2D,TEX_END_LOSE);
		 else
			 glBindTexture(GL_TEXTURE_2D,TEX_END_WIN);
		 glEnable(GL_TEXTURE_2D);



		 glColor3f(1,1,1); // metto il colore neutro (viene moltiplicato col colore texture, componente per componente)
		 glDisable(GL_LIGHTING); // disabilito il lighting OpenGL standard (lo faccio con la texture)

		 glCallList(screen_name);
		 glEnable(GL_LIGHTING);
}






void GameControl_handler::DrawSky()
{



	glBindTexture(GL_TEXTURE_2D,TEX_SKY);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE , GL_SPHERE_MAP); // Env map
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE , GL_SPHERE_MAP);
	glColor3f(1,1,1);
	glDisable(GL_LIGHTING);
	glPushMatrix();

	DrawSphere(300.0, 20, 20);


	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);


}


void GameControl_handler::glShadowProjection(float * l, float * e, float * n)
{
  float d, c;
  float mat[16];

  // These are c and d (corresponding to the tutorial)

  d = n[0]*l[0] + n[1]*l[1] + n[2]*l[2];
  c = e[0]*n[0] + e[1]*n[1] + e[2]*n[2] - d;

  // Create the matrix. OpenGL uses column by column
  // ordering

  mat[0]  = l[0]*n[0]+c;
  mat[4]  = n[1]*l[0];
  mat[8]  = n[2]*l[0];
  mat[12] = -l[0]*c-l[0]*d;

  mat[1]  = n[0]*l[1];
  mat[5]  = l[1]*n[1]+c;
  mat[9]  = n[2]*l[1];
  mat[13] = -l[1]*c-l[1]*d;

  mat[2]  = n[0]*l[2];
  mat[6]  = n[1]*l[2];
  mat[10] = l[2]*n[2]+c;
  mat[14] = -l[2]*c-l[2]*d;

  mat[3]  = n[0];
  mat[7]  = n[1];
  mat[11] = n[2];
  mat[15] = -d;

  // Finally multiply the matrices together *plonk*
  glMultMatrixf(mat);
}





