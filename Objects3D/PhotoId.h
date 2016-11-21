#ifndef PHOTOID_H_
#define PHOTOID_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "../Utils/Defines.h"
#include "../Utils/polygons.h"


class PhotoId
{
public:

	GLuint foto_list_name;  //display list

	PhotoId();


	void Init();
	void DrawPhoto();

};

#endif
