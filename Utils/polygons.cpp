#include "polygons.h"

void DrawSphere(double r, int lats, int longs) {
int i, j;
  for(i = 0; i <= lats; i++) {
     double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
     double z0  = sin(lat0);
     double zr0 =  cos(lat0);

     double lat1 = M_PI * (-0.5 + (double) i / lats);
     double z1 = sin(lat1);
     double zr1 = cos(lat1);

     glBegin(GL_QUAD_STRIP);
     for(j = 0; j <= longs; j++) {
        double lng = 2 * M_PI * (double) (j - 1) / longs;
        double x = cos(lng);
        double y = sin(lng);

//le normali servono per l'EnvMap
        glNormal3f(x * zr0, y * zr0, z0);
        glVertex3f(r * x * zr0, r * y * zr0, r * z0);
        glNormal3f(x * zr1, y * zr1, z1);
        glVertex3f(r * x * zr1, r * y * zr1, r * z1);
     }
     glEnd();
  }
}


void DrawRectangle(float cx, float cy)
{



	 glBegin(GL_QUADS);
	  glColor3f(0,0.5,0.5);
	  glVertex2d(0,SCR_H);
	  glVertex2d(200,SCR_H);
	  glVertex2d(200,SCR_H-100);
	  glVertex2d(0,SCR_H-100);
	 glEnd();

}

void DrawCircle(float cx, float cy, float r, int num_segments)  //cerchio sul piano xy
{
	glBegin(GL_POLYGON);
	for(int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		float tx = cosf(theta) * 0.5 + 0.5;
		float ty = sinf(theta) * 0.5 + 0.5;

		glTexCoord2f(-tx,-ty); //cosi la foto viene ribaltata
		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}

void DrawCircleHole(float cx, float cz, float r, int num_segments)  //cerchio sul piano xz
{
	glBegin(GL_POLYGON);
		glColor3f(1,1,1);
		for(int ii = 0; ii < num_segments; ii++)
		{
			float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

			float x = r * cosf(theta);//calculate the x component
			float z = r * sinf(theta);//calculate the y component
			float tx = cosf(theta) * 0.5 + 0.5;
			float ty = sinf(theta) * 0.5 + 0.5;

			glTexCoord2f(-tx,-ty); //cosi la foto viene ribaltata

			glVertex3f(x + cx, 0.1f,z + cz);//output vertex

		}
		glEnd();
}


// setta le matrici di trasformazione in modo
// che le coordinate in spazio oggetto siano le coord
// del pixel sullo schemo
void  SetCoordToPixel(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(-1,-1,0);
  glScalef(2.0/SCR_W, 2.0/SCR_H, 1);
}
