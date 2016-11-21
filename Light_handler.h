#ifndef LIGHT_HANDLER_H_
#define LIGHT_HANDLER_H_

#include "baseclass/Handler.h"

class Light_handler : public Handler
{

private:

	GLfloat luce_ambiente[4];
	GLfloat luce_diffusa[4];
	GLfloat luce_speculare[4];


public:

	GLfloat posizione_luce[4];
	bool state;
	bool gouraud;
	Light_handler();
	Light_handler(GameStatus* g);
	~Light_handler();

	void Init();
	void SetPositionLight(GLfloat x, GLfloat y, GLfloat z);


};

#endif
