#include "GameStatus.h"
#include "../Sound_handler.h"
#include "../Light_handler.h"

void GameStatus::LoadNewGame()
{
	//funzione per inizializzare tutto a nuovo gioco
	actualState = LOADING;
	losing = true;
	score = 0;
	gameTime= Timer(TIME_LEFT);
	crystals.reserve(NUM_MAX_CRYSTALS);
	hourglasses.reserve(NUM_MAX_HOURGLASSES);
	bombs.reserve(NUM_MAX_BOMBS);

	myPhoto.Init();
	miniMap.Init();
	speedometer.Init();
	world.Init();

	srand(time(NULL)); //genero seed random

	//genero posizioni random per gli oggetti
	int i;
	for(i=0;i<NUM_MAX_CRYSTALS;i++)    //genero i cristalli
	{

		crystals.push_back(Crystal());
		crystals.at(i).Init();
		crystals.at(i).px =  (rand() % S_FLOOR_SIZE) - S_FLOOR_SIZE / 2;
		crystals.at(i).pz = (rand() % S_FLOOR_SIZE)  - S_FLOOR_SIZE / 2 ;
	}
	crystals.resize(NUM_MAX_CRYSTALS);



	for(i=0;i<NUM_MAX_HOURGLASSES;i++)    //genero le clessidre
	{
		hourglasses.push_back(Hourglass());
		hourglasses.at(i).Init();
		hourglasses.at(i).px =  (rand() % S_FLOOR_SIZE) - S_FLOOR_SIZE / 2;
		hourglasses.at(i).pz = (rand() % S_FLOOR_SIZE) - S_FLOOR_SIZE / 2;

	}
	hourglasses.resize(NUM_MAX_HOURGLASSES);


	for(i=0;i<NUM_MAX_BOMBS;i++)    //genero le bombe
	{
		bombs.push_back(Bomb());
		bombs.at(i).Init();
		bombs.at(i).px =  (rand() % S_FLOOR_SIZE) - S_FLOOR_SIZE / 2;
		bombs.at(i).pz = (rand() % S_FLOOR_SIZE) - S_FLOOR_SIZE / 2;
		bombs.at(i).py = 0.8;
	}
	bombs.resize(NUM_MAX_BOMBS);


}

void GameStatus::DetectCollisionKart()  //collisione veramente semplice
{

	int i;

	for(i=0;i<NUM_MAX_CRYSTALS;i++)   //per ogni cristallo effettuo un check.
		Check_Collision_Crystal(i);

	for(i=0;i<NUM_MAX_HOURGLASSES;i++)   //per ogni clessidra del tempo effettuo un check.
		Check_Collision_Hourglass(i);

	for(i=0;i<NUM_MAX_BOMBS;i++)   //per ogni bomba del tempo effettuo un check.
			Check_Collision_Bomb(i);

	for(i=0;i<NUM_MAX_HOLES;i++)   //controllo per ogni buca
			Check_inHole(i);

	Check_collision_wall();  //controllo della collisione contro i muri
}

void GameStatus::Check_Collision_Crystal(int i)
{
	if(crystals.at(i).visible && (kart.px> (crystals.at(i).px - 1) && kart.px< (crystals.at(i).px + 1)) &&
				(kart.py> (crystals.at(i).py - 1) && kart.py< (crystals.at(i).py + 1)) &&
				(kart.pz> (crystals.at(i).pz - 1) && kart.pz< (crystals.at(i).pz + 1)))
	{
			std::cout<<"collisione cristallo\n"<<std::endl;
			crystals.at(i).visible = false;
			score ++;
			kart.turboAvailable = true;
			kart.timerTurbo = Timer(MAX_TIME_TURBO); //metto 3 sec di timer
			kart.timerTurbo.LoadNewTime();
			sh->PlayEffect(1);
			std::cout<<"Turbo attivo!\n";
	}
}

void GameStatus::Check_Collision_Hourglass(int i)
{
	if(hourglasses.at(i).visible && (kart.px> (hourglasses.at(i).px - 1) && kart.px< (hourglasses.at(i).px + 1)) &&
				(kart.py> (hourglasses.at(i).py - 1) && kart.py< (hourglasses.at(i).py + 1)) &&
				(kart.pz> (hourglasses.at(i).pz - 1) && kart.pz< (hourglasses.at(i).pz + 1)))
	{
			std::cout<<"collisione clessidra\n"<<std::endl;
			hourglasses.at(i).visible = false;
			gameTime.time_left +=2;
			sh->PlayEffect(4);
	}
}

void GameStatus::Check_Collision_Bomb(int i)
{
	if(bombs.at(i).visible && (kart.px> (bombs.at(i).px - 1) && kart.px< (bombs.at(i).px + 1)) &&
				(kart.py> (bombs.at(i).py - 1) && kart.py< (bombs.at(i).py + 1)) &&
				(kart.pz> (bombs.at(i).pz - 1) && kart.pz< (bombs.at(i).pz + 1)))
	{
			std::cout<<"collisione Bomba\n"<<std::endl;
			bombs.at(i).visible = false;
			kart.stopActive = true;
			kart.timeStop = Timer(2);
			kart.timeStop.LoadNewTime();
			sh->PlayEffect(3);

	}
}

void GameStatus::Check_inHole(int i)
{
	if(kart.px >= world.holes.at(i).px-1.5 && kart.px <= world.holes.at(i).px+1.5 &&
			kart.pz >= world.holes.at(i).pz-1.5 && kart.pz <= world.holes.at(i).pz+1.5	)
	{
		std::cout<<"buca\n"<<std::endl;
		kart.px=kart.py=kart.pz= 0;
		kart.facing = 0;
		kart.vx = kart.vy = kart.vz = 0;
		kart.turboAvailable = false;
		kart.accMax = 0.0011;
		sh->PlayEffect(2);
	}


}


void GameStatus::Check_collision_wall()
{

	if(!(kart.px - 1 > -S_FLOOR_SIZE &&  kart.px + 1 < S_FLOOR_SIZE
			&& kart.pz - 1 > -S_FLOOR_SIZE &&  kart.pz + 1 < S_FLOOR_SIZE))
	{
		kart.vx = -kart.vx/2; //il muro mi rispedisce nella direzione da cui provengo
		kart.vz = -kart.vz/2;
	}
}

