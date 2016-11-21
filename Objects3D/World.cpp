#include "World.h"




void World::Init()
{



	float x,z;
	const int K=50; //disegna K x K quads


	holes.reserve(NUM_MAX_HOLES);

	int i;
	for(i=0;i<NUM_MAX_HOLES;i++)    //genero i portali
	{
		holes.push_back(Hole());
		x = (i==0 || i==2) ? 0 : (S_FLOOR_SIZE-2) * (i==1 ? -1 : 1);
		z = (i==1 || i==3) ? 0 : (S_FLOOR_SIZE-2) * (i==0 ? -1 : 1);
		holes.at(i).Init(x,z);
	}
	holes.resize(NUM_MAX_HOLES);


	world_list = glGenLists(1);  //display list per il floor
	glNewList(world_list,GL_COMPILE);

	glEnable(GL_TEXTURE_2D);


		  glBindTexture(GL_TEXTURE_2D,TEX_ROAD);

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


	display_list = glGenLists(1);    //display list per i muri

    glNewList(display_list,GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D,TEX_WALL);
		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);



		//creo i muri  (ogni muro è composto da 2 rettangoli)
	for(i=0;i<4;i++)
	{
		glPushMatrix();

		switch(i)
		{
		case 0:
			glTranslatef(0,0,-S_FLOOR_SIZE);
			break;
		case 1:
			glTranslatef(S_FLOOR_SIZE,0,0);
			glRotatef(90,0,1,0);
			break;
		case 2:
			glTranslatef(0,0,S_FLOOR_SIZE);
			break;
		case 3:
			glTranslatef(-S_FLOOR_SIZE,0,0);
			glRotatef(90,0,1,0);
			break;

		}
		 glBegin(GL_QUADS);
			   glColor3f(1, 1, 1); // colore uguale x tutti i quads
			   glTexCoord2f(0,1);
			   glVertex3f(-S_FLOOR_SIZE, 5 , 0);

			glTexCoord2f(1,1);
			glVertex3f(0, 5 , 0);
			glTexCoord2f(1,0);
			glVertex3f(0, 0 , 0);
			glTexCoord2f(0,0);
			glVertex3f(-S_FLOOR_SIZE, 0 , 0);

	     glEnd();

	     glBegin(GL_QUADS);
		   glColor3f(1, 1, 1); // colore uguale x tutti i quads
		   glTexCoord2f(0,1);
		   glVertex3f(-0, 5 , 0);

		 glTexCoord2f(1,1);
		 glVertex3f(S_FLOOR_SIZE, 5 , 0);
		 glTexCoord2f(1,0);
		 glVertex3f(S_FLOOR_SIZE, 0 , 0);
		 glTexCoord2f(0,0);
		 glVertex3f(0, 0 , 0);

		 glEnd();

		 glPopMatrix();
	}



	   glEndList();


}


void World::Render()
{


	glDisable(GL_LIGHTING);


//     //disegno assi del mondo
//	  DrawAxis();

	  //disegno il piano
	  glCallList(world_list);


	  //disegno i portali
	   int i;
	   for(i= 0; i<NUM_MAX_HOLES;i++)
		   holes.at(i).Render();

	   //disegno i muri
	   glCallList(display_list);


	glEnable(GL_LIGHTING); //riattivo le luci

}


