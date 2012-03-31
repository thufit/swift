#ifndef _TRAFFIC_H_
#define _TRAFFIC_H_

#include <vector>

#include "simulator.h"
#include "cell.h"

using std::vector;

class Traffic
{
public:
	int BernoulliDistribution(vector<Cell>& vc);
	int OnOff();
};

#endif