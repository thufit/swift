#ifndef TRAFFIC_H_
#define TRAFFIC_H_

#include <vector>

#include "simulator.h"
#include "cell.h"

using std::vector;

namespace traffic
{
	void Bernoulli(vector<Cell>& vc, double p); // Bounuli i.i.d
	void OnOff(vector<Cell>& vc, double p, double q);
}

#endif