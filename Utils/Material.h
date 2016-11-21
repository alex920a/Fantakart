#ifndef _MATERIAL_
#define _MATERIAL_

#include <GL/gl.h>
#include <GL/glu.h>

class Material{

private:

	GLfloat ambient_r;
	GLfloat ambient_g;
	GLfloat ambient_b;

	GLfloat diffuse_r;
	GLfloat diffuse_g;
	GLfloat diffuse_b;

	GLfloat specular_r;
	GLfloat specular_g;
	GLfloat specular_b;

	GLfloat emission_r;
	GLfloat emission_g;
	GLfloat emission_b;



public:

	Material(GLfloat ar,GLfloat ag,GLfloat ab,GLfloat dr,GLfloat dg,GLfloat db,GLfloat sr,GLfloat sg,GLfloat sb,
			GLfloat er,GLfloat eg,GLfloat eb){

		ambient_r=ar; ambient_g=ag; ambient_b= ab;
		diffuse_r=dr; diffuse_g=dg; diffuse_b=db;
		specular_r=sr; specular_g=sg; specular_b=sb;
		emission_r=er; emission_g=eg; emission_b=eb;
	}


	void active()
	{


		GLfloat ambient[]= {ambient_r, ambient_g, ambient_b, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);

		GLfloat diffuse[]={diffuse_r,diffuse_g,diffuse_b,1.0};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

		GLfloat specular[]={specular_r, specular_g,specular_b,1.0};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);

		GLfloat emission[]={emission_r,emission_g,emission_b,1.0};
		glMaterialfv(GL_FRONT, GL_EMISSION,emission);

	}

};



#endif
