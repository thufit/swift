#include "util.h"

// Return 1 as probability p
int util::Probability(double p)
{
	static boost::mt19937 gen;
	double probabilities[] = {1 - p, p};
	boost::random::discrete_distribution<> dist(probabilities);

	return dist(gen);
}

// Return a integer in the range of [0, n - 1] as probability 1/n
int util::Uniform(int n)
{
	static boost::mt19937 gen;
	assert(n >= 1);
	if (n > 1)
	{
		boost::random::uniform_int_distribution<> dist(0, n - 1);
		return dist(gen);
	}
	if (n == 1)
		return 0;
	else
	{
		std::cout << "absurd";
		assert(1);
		return -1;
	}
}

//// Return the current time of simulation
//long util::get_current_time()
//{
//	return g_CurrentTime;
//}
//



//#if 0
//// Time elapse 1 cycle
//void Util::time_elapse()
//{
//	++g_CurrentTime;
//}
//#endif