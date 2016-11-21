#include "../baseclass/Model3D.h"
#include "../Utils/polygons.h"

class Hole : Model3D
{


	public:
		void Init(float x, float z);
		void Render();


		Hole();



		float px,pz; //posizione iniziale
		GLuint displayList;


		virtual ~Hole();
};
