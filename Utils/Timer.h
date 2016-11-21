#ifndef TIMER_H_
#define TIMER_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <sstream>
#include <iostream>


class Timer
{
public:
		int time_left;
		int time_prec;
		int start_time;

		Timer();
		Timer(int sec);

		void LoadNewTime();
		void ComputeNewTime();
		bool TimerEnded();
		void printTimeLeft();
};

#endif
