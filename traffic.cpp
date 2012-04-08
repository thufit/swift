#include "traffic.h"
#include "util.h"
#include "config.h"

extern Simulator* sim;

void Traffic::BernoulliDistribution(vector<Cell> & vc, double p)
{
	for (int i = 0; i < (int)vc.size(); ++i)
	{
		if (Util::prob_gen(p))
		{
			vc[i].setBirth(sim->getTime());
			vc[i].setSrc(i);
			vc[i].setDest(Util::uniform_gen(Config::nr_queue));
		}
	}
}

