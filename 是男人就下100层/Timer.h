﻿
#pragma once
#include <ctime>
#include<iostream>
#include<windows.h>
#include"unit.h"
//璁℃椂鍣?
class Timer
{
public:
	static bool timer(clock_t ms, int num);
	static void beginkeep()
	{
		time = clock();
	}
	static void endkeep()
	{
		int endtime = clock();
		//Sleep(FRAME - (endtime - time));
		Sleep(100);
	}
	static int time;
};


