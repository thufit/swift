#ifndef UTIL_H_
#define UTIL_H_

#include "boost/random.hpp"

//static long g_CurrentTime = 0;

namespace util
{
	int GenerateWithProbability(double p);
	int UniformGenerate(int u);

	//long get_current_time();
	//void time_elapse();
}

#endif
