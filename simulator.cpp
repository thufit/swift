#include "simulator.h"

Simulator* Simulator::getSimulator()
{
	if (_sim == 0)
	{
		_sim = new Simulator();
	}

	return _sim;
}