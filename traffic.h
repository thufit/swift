#ifndef TRAFFIC_H_
#define TRAFFIC_H_

#include <vector>

#include "simulator.h"
#include "cell.h"

using std::vector;

namespace traffic
{
	void BernoulliDistribution(vector<Cell>& vc, double p);
	void OnOff();
}

#endif