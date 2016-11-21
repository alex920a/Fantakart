#ifndef MINIMAP_H_
#define MINIMAP_H_


#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "../Utils/Defines.h"
#include "../Utils/polygons.h"




class MiniMap
{
public:

		GLuint map_list_name;  //display list



		MiniMap();


		void Init();
		void DrawMap();
		void DrawElement(float cx, float cy,float px,float py,int type_object); //disegna sulla minimappa gli oggetti in giro
};

#endif
