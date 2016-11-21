#include "../baseclass/Model3D.h"


class Crystal : public Model3D
{


	public:
		void Init();
		void Render();
		void DoStep();

		Crystal();

		Mesh* crystal;

		float px,py,pz; //posizione iniziale

		float angle_rot; //velocita rotazione cubo
		float jump_trasl; //il cubo "salta"
		bool visible;


		Material* emerald;


		virtual ~Crystal();
};
