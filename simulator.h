#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "stats.h"

// Sigleton simulator class
class Simulator
{
public:
	static Simulator* GetSimulator();
	static void Elapse();
	static long get_time();

protected:
	Simulator();

private:
	static Simulator* sim_;
	static long time_;
};


#endif