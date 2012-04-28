#include "traffic.h"
#include "util.h"
#include "config.h"

extern Simulator* g_sim;

void traffic::BernoulliDistribution(vector<Cell>& vc, double p)
{
	for (int i = 0; i < (int)vc.size(); ++i)
	{
		if (util::GenerateWithProbability(p))
		{
			//std::cout << " generating 1" << std::endl;
			vc[i].set_birth(g_sim->get_time());
			vc[i].set_src(i);
			vc[i].set_dest(util::UniformGenerate(config::kQueueNumber));
			//std::cout << " dest = "<< vc[i].get_dest() << std::endl;
		}
	}
}


void traffic::OnOff()
{

}
