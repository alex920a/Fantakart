#include "Light_handler.h"

Light_handler::Light_handler()
{
	state = true;
}
Light_handler::Light_handler(GameStatus* g) : Handler(g){state = true;}
Light_handler::~Light_handler(){}

void Light_handler::Init()
{

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,luce_ambiente);

	//luce 0 luce ambientale
	luce_ambiente[0] = 0.8;
	luce_ambiente[1] = 0.5;
	luce_ambiente[2] = 0.5;
	luce_ambiente[3] = 1;

	luce_diffusa[0] = 0.9;
	luce_diffusa[1] = 0.9;
	luce_diffusa[2] = 0.8;
	luce_diffusa[3] = 1.0;

	luce_speculare[0] = 1;
	luce_speculare[1] = 1;
	luce_speculare[2] = 1;
	luce_speculare[3] = 1;

	posizione_luce[0] = 20;
	posizione_luce[1] = 20;
	posizione_luce[2] = 20;
	posizione_luce[3] = 0;


	glLightfv(GL_LIGHT0, GL_AMBIENT, luce_ambiente);     // Setta la luce Ambientale
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luce_diffusa);     // Setta la luce Diffusa
	glLightfv(GL_LIGHT0, GL_SPECULAR,luce_speculare);    // Posiziona la luce
	glLightfv(GL_LIGHT0, GL_POSITION,posizione_luce);    // Posiziona la luce


	//abilito le luci
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE); // opengl, per favore, rinormalizza le normali
								  // prima di usarle
	glFrontFace(GL_CW); // consideriamo Front Facing le facce ClockWise

	glEnable(GL_POLYGON_OFFSET_FILL); // caro openGL sposta i
	                                    // frammenti generati dalla
	                                    // rasterizzazione poligoni
	glPolygonOffset(1,1);             // indietro di 1

	glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glShadeModel(GL_SMOOTH);

	state = true;
	gouraud = true;

}

void Light_handler::SetPositionLight(GLfloat x, GLfloat y, GLfloat z)
{
	posizione_luce[0] = x;
	posizione_luce[1] = y;
	posizione_luce[2] = z;
	glLightfv(GL_LIGHT0, GL_POSITION,posizione_luce);  //setto la posizione della luce


}



