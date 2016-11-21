#include "CameraHandler.h"

CameraHandler::CameraHandler()
{
	camera_state = BEHIND;
	camera_distance = 4;
	camera_height = 0;
}

CameraHandler::CameraHandler(GameStatus *g): Handler(g)
{
	camera_state = BEHIND;
	camera_distance = 4;
	camera_height = 0;
}
CameraHandler::~CameraHandler()
{
	camera_state = BEHIND;
	camera_distance = 4;
	camera_height = 0;
}

void CameraHandler::Init()
{


	cam_angle[0] = 0;
	cam_angle[1] = 0;
	cam_angle[2] = 0;


	camera_state = BEHIND;
}

void CameraHandler::SetPOVCamera(int type)
{
	switch(type)
	{
		case 0:
			camera_state = BEHIND;
		break;

		case 1:
			camera_state = TOP;
		break;

		case 2:
			camera_state = LATERAL;
		break;
	}
}


void CameraHandler::SetCamera()
{
	double ex,ey,ez,cx, cy, cz;
	double angle= state->kart.facing;
	double cosf = cos(angle*M_PI/180.0);
	double sinf = sin(angle*M_PI/180.0);
	double camd , plus_d = 0;
	double camh ;
	double px = state->kart.px;
	double py = state->kart.py;
	double pz = state->kart.pz;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	 /* Set our perspective */
	gluPerspective( 90.0f, (float)SCR_W/SCR_H, 1.0f, 1000.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	switch(state->camera->camera_state)
	{
		case  BEHIND:
			//state->camera->camera_distance=4;
			state->camera->camera_height=2;
			break;
		case  TOP:
			//state->camera->camera_distance=2.5;
			state->camera->camera_height=10.0;
			plus_d = 5;
			break;
		case  LATERAL:
			//state->camera->camera_distance=3;
			state->camera->camera_height=2;
			angle -= 45.0;
			cosf = cos(angle*M_PI/180.0);
			sinf = sin(angle*M_PI/180.0);
			break;	 //da modificare questi


	}

	camd = state->camera->camera_distance;
	camh = state->camera->camera_height;

	ex = px + camd*sinf;
	ey = py + camh;
	ez = pz + camd*cosf;
	cx = px - camd*sinf;
	cy = py + camh;
	cz = pz - camd*cosf;


	glRotatef(state->camera->cam_angle[0],1,0,0);
	glRotatef(state->camera->cam_angle[1],0,1,0);
	gluLookAt(ex,ey+ plus_d,ez,cx,cy,cz,0.0,1.0,0.0);   //posiziono la camera

}
