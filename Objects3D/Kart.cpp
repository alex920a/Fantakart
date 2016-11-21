#include "Kart.h"

//Mesh chassis((char *)"Ferrari_chassis.obj"); // chiama il costruttore
//Mesh wheelBR1((char *)"Ferrari_wheel_back_R.obj");
//Mesh wheelFR1((char *)"Ferrari_wheel_front_R.obj");
//Mesh wheelBR2((char *)"Ferrari_wheel_back_R_metal.obj");
//Mesh wheelFR2((char *)"Ferrari_wheel_front_R_metal.obj");

void Controller::Init(){
  for (int i=0; i<NKEYS; i++) key[i]=false;  //iniziallizzo tutti i tasti del controller


}

// da invocare quando e' stato premuto/rilasciato il tasto numero "keycode"
void Controller::EatKey(int keycode, int* keymap, bool pressed_or_released)
{
  for (int i=0; i<NKEYS; i++)
    if (keycode==keymap[i])
    	{
    		//std::cout<<"Premuto o rilasciato tasto: "<< i <<std::endl;
    		key[i]=pressed_or_released;
    	}
}

// da invocare quando e' stato premuto/rilasciato jbutton"
void Controller::Joy(int keymap, bool pressed_or_released)
{
    key[keymap]=pressed_or_released;
}


Kart::~Kart()
{

}
Kart::Kart()
{
	accMax = accTurbo= attrito= attritoX = attritoY = attritoZ = 0;
	px=py=pz=vx=vy=vz=grip=facing=sterzo=velModule=0;
	mozzoA = mozzoP = 0;
	velRitornoSterzo = velSterzo = 0;
	chassis = wheelBR1  = wheelFR1  = NULL;
	raggioRuotaA = raggioRuotaP = 0;
	turboAvailable = false;
	stopActive = false;
	//material = NULL;

}

Kart::Kart(int selection):Model3D(){
	Init(selection);

}


void Kart::Init(int selection)
{
	switch(selection) //cambio di mesh e attributi in base al player
	{
		case 0:
			chassis  = new Mesh((char *)"res/models/KartOxide/KartOxide.obj",-0.05,0.05,-0.05);
			 wheelBR1 = new Mesh((char *)"res/models/KartOxide/back_Wheel.obj");
			 wheelFR1 = new Mesh((char *)"res/models/KartOxide/front_Wheel.obj");
			 velSterzo=2.4;         // A
			 velRitornoSterzo=0.93; // B, sterzo massimo = A*B / (1-B)
			 accMax = 0.0011;
			 accTurbo = accMax * 2;
			 break;
		case 1:
			 chassis  = new Mesh((char *)"res/models/KartCrash/KartCrash.obj",-0.05,0.05,-0.05);
			 wheelBR1 = new Mesh((char *)"res/models/KartCrash/back_Wheel.obj");
			 wheelFR1 = new Mesh((char *)"res/models/KartCrash/front_Wheel.obj");
			 velSterzo=1.4;         // A
			 velRitornoSterzo=0.93; // B, sterzo massimo = A*B / (1-B)
			 accMax = 0.0015;
			 accTurbo = accMax * 3;
			 break;
		case 2:
			chassis  = new Mesh((char *)"res/models/KartCortex/KartCortex.obj",-0.05,0.05,-0.05);
			 wheelBR1 = new Mesh((char *)"res/models/KartCortex/back_Wheel.obj");
			 wheelFR1 = new Mesh((char *)"res/models/KartCortex/front_Wheel.obj");
			 velSterzo=3;         // A
			 velRitornoSterzo=0.93; // B, sterzo massimo = A*B / (1-B)
			 accMax = 0.0005;
			 accTurbo = accMax * 4;
			 break;
	}


	turboAvailable = false;
	px=pz=facing=0;
	py= 0.0f;
	vx=vy=vz=0;

	mozzoA=mozzoP=sterzo= 0;

	 // inizializzo la struttura di controllo
	  controller.Init();



	  // attriti: percentuale di velocita' che viene mantenuta
	  // 1 = no attrito
	  // <<1 = attrito grande
	  attritoZ = 0.991;  // piccolo attrito sulla Z (nel senso di rotolamento delle ruote)
	  attritoX = 0.8;  // grande attrito sulla X (per non fare slittare la macchina)
	  attritoY = 1.0;  // attrito sulla y nullo

	  // Nota: vel max = accMax*attritoZ / (1-attritoZ)

	  raggioRuotaA = 0.25;
	  raggioRuotaP = 0.35;

	  grip = 0.45; // quanto il facing macchina si adegua velocemente allo sterzo


}


void Kart::Render(int color_base)
{


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);


	  glPushMatrix();
	  glTranslatef(px,py,pz);
	  glRotatef(facing, 0,1,0);


	  // disegna la carliga con una mesh
	  glPushMatrix();
	  glScalef(-0.08,0.08,-0.08); // patch: riscaliamo la mesh di 1/10  (c'e il segno '-' per "ruotare simmetricamente" )



	  switch(color_base)
	  {
	  	  	case 0:
		  	  	  	  	glBindTexture(GL_TEXTURE_2D, TEX_OXIDE);
		  	  	  	  	//material = new Material(0,0,0,0.376320,0.376320,0.376320,0,0,0,0,0,0);
		  	  			break;
	  	  	case 1:
						glBindTexture(GL_TEXTURE_2D, TEX_CRASH);
						//material = new Material(0,0,0,0.376320,0.376320,0.376320,0,0,0,0,0,0);
						break;
	  	  	case 2:
						glBindTexture(GL_TEXTURE_2D, TEX_CORTEX);
						//material = new Material(0,0,0,0.512,0.512,0.512,0.5,0.5,0.5,0,0,0);
						break;

	  }


	  if(shadowOn)
	  {

		  glDisable(GL_TEXTURE_2D);
	  }
	  else
	  {
		  glEnable(GL_TEXTURE_2D);
		 // material->active();
	  }



	  chassis->Render();


	  for (int i=0; i<2; i++) {
	    // i==0 -> disegno ruote destre.
	    // i==1 -> disegno ruote sinistre.
	    int sign;
	    if (i==0) sign=1; else sign=-1;
	    glPushMatrix();
	      if (i==1) {
	        glTranslatef(0,+wheelFR1->Center().Y() , 0);
	        glRotatef(180, 0,0,1 );
	        glTranslatef(0,-wheelFR1->Center().Y(), 0);


	      }

	      glTranslate(  wheelFR1->Center() );
	      glRotatef( sign*sterzo,0,1,0);
	      glRotatef(-sign*mozzoA,1,0,0);
	      glTranslate( -wheelFR1->Center() );

	      glColor3f(.3,.3,.3);
	      wheelFR1->Render();

	    glPopMatrix();

	    glPushMatrix();
	      if (i==1) {
	        glTranslatef(0,+wheelBR1->Center().Y(), 0);
	        glRotatef(180, 0,0,1 );
	        glTranslatef(0,-wheelBR1->Center().Y(), 0);
	      }

	      glTranslate(  wheelBR1->Center() );
	      glRotatef(-sign*mozzoA,1,0,0);
	      glTranslate( -wheelBR1->Center() );

	      glColor3f(.3,.3,.3);
	      wheelBR1->Render();
	    glPopMatrix();
	  }
	  glPopMatrix();

	  glPopMatrix();



}

void Kart::DoStep(){
  // computiamo l'evolversi della macchina

  float vxm, vym, vzm; // velocita' in spazio macchina
  float accTemp=accMax;

  // da vel frame mondo a vel frame macchina
  float cosf = cos(facing*M_PI/180.0);
  float sinf = sin(facing*M_PI/180.0);
  vxm = +cosf*vx - sinf*vz;
  vym = vy;
  vzm = +sinf*vx + cosf*vz;

  // gestione dello sterzo
  if (controller.key[Controller::LEFT]) sterzo+=velSterzo;
  if (controller.key[Controller::RIGHT]) sterzo-=velSterzo;
  sterzo*=velRitornoSterzo; // ritorno a volante fermo

  if(turboAvailable) //turbo attivato
  {
	  timerTurbo.ComputeNewTime(); //aggiorniamo il timer del turbo


	  if(!timerTurbo.TimerEnded())
	  {
		 // std::cout<<"Turbo attivo!\n";
		  accTemp = accTurbo;
	  }
	  else
	  {
		  //std::cout<<"Turbo esaurito!\n";
		  turboAvailable = false;
		  accTemp= accMax; //ripristino il vecchio turbo
	  }

  }
  else
	  accTemp= accMax;



  if (controller.key[Controller::ACC]) vzm-=accTemp;// accelerazione in avanti
  if (controller.key[Controller::DEC]) vzm+=accTemp;// accelerazione indietro



  // attriti (semplificando)
  vxm*=attritoX;
  vym*=attritoY;
  vzm*=attritoZ;

  // l'orientamento della macchina segue quello dello sterzo
  // (a seconda della velocita' sulla z)
  facing = facing - (vzm*grip)*sterzo;

  // rotazione mozzo ruote (a seconda della velocita' sulla z)
  float da ; //delta angolo
  da=(360.0*vzm)/(2.0*M_PI*raggioRuotaA);
  mozzoA+=da;
  da=(360.0*vzm)/(2.0*M_PI*raggioRuotaP);
  mozzoP+=da;

  // ritorno a vel coord mondo
  vx = +cosf*vxm + sinf*vzm;
  vy = vym;
  vz = -sinf*vxm + cosf*vzm;
  velModule = sqrt(vx*vx+ vy*vy+vz*vz);

  // posizione = posizione + velocita * delta t (ma e' delta t costante)
  px+=vx;
  py+=vy;
  pz+=vz;

}
