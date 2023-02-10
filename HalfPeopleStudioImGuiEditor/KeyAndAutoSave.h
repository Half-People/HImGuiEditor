#pragma once
#include "Porject.h"
#include <thread>
static std::thread AutoSaveThread;

static void KeyTick()
{

}


static void AutoSaveTick()
{
	while (true)
	{
		if (AutoSave::AutoSave)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((long long)((AutoSave::Interval * 60) * 1000)));
			Porject::SavePorject();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		}
	}
}

static void AutoSaveInit()
{
	AutoSaveThread = std::thread(AutoSaveTick);
}