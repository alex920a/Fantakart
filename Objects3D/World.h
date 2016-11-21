#include "../baseclass/Model3D.h"
#include "Hole.h"
#include "../Utils/Defines.h"

#include <time.h>
#include <stdlib.h>

class World : Model3D
{


	public:
		void Init();
		void Render();
		World(){ Init();}

		std::vector<Hole> holes;  //portali

		//stato del mondo

		GLuint display_list;
		GLuint world_list;
};
