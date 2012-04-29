#include "traffic.h"
#include "util.h"
#include "config.h"

extern Simulator* g_sim;

void traffic::Bernoulli(vector<Cell>& vc, double p)
{
	for (int i = 0; i < (int)vc.size(); ++i)
	{
		if (util::Probability(p))
		{
			//std::cout << " generating 1" << std::endl;
			vc[i].set_birth(g_sim->get_time());
			vc[i].set_src(i);
			vc[i].set_dest(util::Uniform(config::kPortCount));
			//std::cout << " dest = "<< vc[i].get_dest() << std::endl;
		}
	}
}


void traffic::OnOff(vector<Cell>& vc, double p, double q)
{
	enum State { kOn, kOff};
	static State state[config::kPortCount];
	static int dest[config::kPortCount];
	static bool first = true;

	if (first)
	{
		first = false;
		for (int i = 0; i < config::kPortCount; ++i)
			state[i] = kOff;
	}
	
	for (int i = 0; i < config::kPortCount; ++i)
	{
		if (state[i] == kOn)
		{
			if (util::Probability(1 - p))
			{
				state[i] = kOff;
			}
		}
		else	// state[i] == kOff
		{
			if (util::Probability(1 - q))
			{
				state[i] = kOn;
				dest[i] = util::Uniform(config::kPortCount);
			}
		}
	}

	for (int i = 0; i < config::kPortCount; ++i)
	{
		if (state[i] == kOn)
		{
			vc[i].set_birth(g_sim->get_time());
			vc[i].set_src(i);
			vc[i].set_dest(dest[i]);
		}
	}
}
