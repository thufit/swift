#include "simulator.h"

Simulator* Simulator::sim_ = 0;
long Simulator::time_ = 0;

Simulator* Simulator::GetSimulator()
{
	if (sim_ == 0)
	{
		sim_ = new Simulator();
	}

	return sim_;
}

Simulator::Simulator()
{
}

void Simulator::Elapse()
{
	++time_;
}

long Simulator::get_time()
{
	return time_;
}