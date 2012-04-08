#include "simulator.h"

Simulator* Simulator::_sim = 0;
long Simulator::_time = 0;

Simulator* Simulator::getSimulator()
{
	if (_sim == 0)
	{
		_sim = new Simulator();
	}

	return _sim;
}

Simulator::Simulator()
{
}

void Simulator::elaspe()
{
	++_time;
}

long Simulator::getTime()
{
	return _time;
}