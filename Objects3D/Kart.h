#include "../baseclass/Model3D.h"
#include "../Utils/Timer.h"


class Controller{   //classe controller per il kart
public:
  enum { LEFT=0, RIGHT=1, ACC=2, DEC=3, NKEYS=4};
  bool key[NKEYS];
  void Init();
  void EatKey(int keycode, int* keymap, bool pressed_or_released);
  void Joy(int keymap, bool pressed_or_released);
  Controller(){Init();} // costruttore
};



class Kart : public Model3D
{




	public:

		Mesh* chassis;
		Mesh* wheelBR1;
		Mesh* wheelFR1;
		//Material* material;

		void Init(int selection);
		void Render(int color_base);
		void DoStep();



		Kart();
		Kart(int selection);


		//stato del kart
		// (DoStep fa evolvere queste variabili nel tempo)
		float px,py,pz,facing; //posizione ed orientamento
		float mozzoA,mozzoP, sterzo;
		float vx,vy,vz ,velModule;
		bool turboAvailable;
		bool stopActive;
		Timer timerTurbo;
		Timer timeStop;


		 // STATS DEL KART
		  // (di solito rimangono costanti)
	    float velSterzo, velRitornoSterzo, accMax,accTurbo, attrito,
			raggioRuotaA, raggioRuotaP, grip,
			attritoX, attritoY, attritoZ; // attriti

		//controller
		Controller controller;

		virtual ~Kart();
};
