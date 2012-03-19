#ifndef _UTIL_H_
#define _UTIL_H_

#include "boost/random.hpp"

static long g_current_time = 0;

namespace Util
{
	int prob_gen(double p);
	int uniform_gen(int u);
	long get_current_time();
	void time_elapse();
}

#endif
