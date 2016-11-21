#include "../baseclass/Model3D.h"

class Bomb : public Model3D
{


	public:
		void Init();
		void Render();
		void DoStep();

		Bomb();

		Mesh* bomb;

		float px,py,pz; //posizione iniziale

		float angle_rot; //velocita rotazione cubo
		float jump_trasl; //il cubo "salta"
		bool visible;
		Material* grey;

		virtual ~Bomb();
};
