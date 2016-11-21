#include "Model3D.h"

Model3D::~Model3D()
{

}

// disegna gli assi nel sist. di riferimento
void Model3D::DrawAxis(){
  const float K=0.10;

  glBegin(GL_LINES);

    glColor3f(0,0,1);      //asse x blu
    glVertex3f( -1,0,0 );
    glVertex3f( +1,0,0 );

    glColor3f(0,1,0);     //asse y green
    glVertex3f( 0,-1,0 );
    glVertex3f( 0,+1,0 );

    glColor3f(1,0,0);     //asse z rosso
    glVertex3f( 0,0,-1 );
    glVertex3f( 0,0,+1.5 );
  glEnd();

  glBegin(GL_TRIANGLES);

  	glColor3f(0,0,1);
    glVertex3f( 0,+1  ,0 );
    glVertex3f( K,+1-K,0 );
    glVertex3f(-K,+1-K,0 );

    glColor3f(0,1,0);
    glVertex3f( +1,   0, 0 );
    glVertex3f( +1-K,+K, 0 );
    glVertex3f( +1-K,-K, 0 );

    glColor3f(1,0,0);
    glVertex3f( 0, 0,+1.5 );
    glVertex3f( 0,+K,+1.5-K );
    glVertex3f( 0,-K,+1.5-K );
  glEnd();

}


