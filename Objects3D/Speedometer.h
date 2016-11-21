#ifndef SPEED_H_
#define SPEED_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
#include "../Utils/Defines.h"
#include "../Utils/polygons.h"


class Speedometer
{
public:
	float rect_center_x, rect_center_y;
	float arrow_center_x, arrow_center_y, arrow_h, arrow_w, arrow_y_reset;
	float h,w;
		GLuint speed_list;  //display list

		Speedometer();
		Speedometer(float cx,float cy, float h, float w);

		void Init();
		void DrawSpeedometer(float velModule);
		void DrawArrow(float velModule);

};




#endif
