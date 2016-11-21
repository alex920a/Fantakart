#ifndef MODEL3D_H_
#define MODEL3D_H_


#include "../Utils/mesh.h"
#include "../Utils/Defines.h"
#include "../Utils/Material.h"

class Model3D
{
	public:

		//posizione dell'oggetto
		float px,py,pz;
		bool shadowOn;
		bool lightOn;


		Model3D(){
			px = py = pz = 0;
			lightOn = false;
			shadowOn = false;
		}

		void DrawAxis();
		virtual void Init(){};
		virtual	void Render(){};
		virtual ~Model3D();


};

#endif /* MODEL3D_H_*/
