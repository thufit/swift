#ifndef UTIL_H_
#define UTIL_H_

#include "boost/random.hpp"

static long g_current_time = 0;

namespace util
{
	int prob_gen(double p);
	int uniform_gen(int u);
	long get_current_time();
	//void time_elapse();
}

#endif
