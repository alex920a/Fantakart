#include "Timer.h"

Timer::Timer()
{
	start_time = 0;
	time_left = 0;
	time_prec = 0;
}

Timer::Timer(int sec)
{
	start_time = 0;
	time_left = sec;
	time_prec = 0;
}

void Timer::LoadNewTime()
{
	start_time = SDL_GetTicks();
	time_prec = 0;
	//std::cout<<" TIME LEFT (sec): "<< time_left<<std::endl;
}

void Timer::ComputeNewTime()
{

	if((SDL_GetTicks() - start_time ) / 1000 >= time_prec + 1)
	{
		time_left --;
		//std::cout<<" TIME LEFT (sec): "<< time_left<<std::endl;
		time_prec =( SDL_GetTicks() - start_time) / 1000;

	}

}

bool Timer::TimerEnded()
{
	if(time_left <= 0)
		return true;
	else
		return false;
}


void Timer::printTimeLeft()
{
	std::cout<<" TIME LEFT (sec): "<< time_left<<std::endl;
}
