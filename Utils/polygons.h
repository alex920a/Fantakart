#ifndef POLYGONS_H_
#define POLYGONS_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include "Defines.h"
#include <math.h>

void DrawCircle(float cx, float cy, float r, int num_segments) ;
void DrawCircleHole(float cx, float cz, float r, int num_segments) ;

void DrawRectangle(float cx, float cy);
void DrawSphere(double r, int lats, int longs);
void SetCoordToPixel();

#endif
