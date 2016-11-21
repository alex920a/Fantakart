#include "../baseclass/Model3D.h"

class Player : Model3D
{


	public:
		void Init(int selection);
		void Render(int selection);


		Player(int selection);

		Mesh* player;

		float px,py,pz; //posizione iniziale


		virtual ~Player();
};
