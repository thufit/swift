#include "util.h"

// Return 1 as probability p
int Util::prob_gen(double p)
{
	static boost::mt19937 gen;
	double probabilities[] = {1 - p, p};
	boost::random::discrete_distribution<> dist(probabilities);

	return dist(gen);
}

// Return a integer in the range of [0, u - 1] as probability 1/u
int Util::uniform_gen(int u)
{
	static boost::mt19937 gen;
	boost::random::uniform_int_distribution<> dist(0, u - 1);

	return dist(gen);
}

// Return the current time of simulation
long Util::get_current_time()
{
	return g_current_time;
}

#if 0
// Time elapse 1 cycle
void Util::time_elapse()
{
	++g_current_time;
}
#endif