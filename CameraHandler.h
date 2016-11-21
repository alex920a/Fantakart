#ifndef CAMERA_HANDLER_H_
#define CAMERA_HANDLER_H_

#include "baseclass/Handler.h"

class CameraHandler : Handler
{
public:



	double cam_angle[3]; //camera orientation
	double camera_distance; //distanza dal kart
	double camera_height;

	Camera_state camera_state;

	CameraHandler(GameStatus *g);
	CameraHandler();
	virtual ~CameraHandler();

	void Init();
	void SetPOVCamera(int type);
	void SetCamera();



};



#endif //CAMERA_HANDLER_H_
