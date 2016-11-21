#include "Hole.h"

void Hole::Init(float x, float z)
{

	px= x;
	pz= z;

	displayList = glGenLists(1);    //display list

	glNewList(displayList,GL_COMPILE);


		glEnable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glBindTexture(GL_TEXTURE_2D, TEX_HOLE);

		DrawCircleHole(px,pz,2,40);


	    glDisable(GL_BLEND);

	    glEndList();

}

Hole::Hole()
{
	Init(0.0f,0.0f);
}

Hole::~Hole()
{

}

void Hole::Render()
{
	glCallList(displayList);
}


