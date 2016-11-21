#include "../baseclass/Model3D.h"

class Hourglass : public Model3D
{


	public:
		void Init();
		void Render();
		void DoStep();

		Hourglass();

		Mesh* hourglass;

		float px,py,pz; //posizione iniziale


		bool visible;

		Material* bronze;

		virtual ~Hourglass();
};
