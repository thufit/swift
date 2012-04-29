#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include<cstdio>
#include<cstring>

#include "config.h"

namespace schedule
{
	enum Scheduling { kMaximumMatching, kPIM, kiSLIP};
	//enum OutputSchedule { kFIFO};

	void MaximumMatching(int request[config::kPortCount][config::kPortCount], int grant[config::kPortCount]);
	void PIM(int request[config::kPortCount][config::kPortCount], int grant[config::kPortCount]);	
	void iSLIP(int request[config::kPortCount][config::kPortCount], int grant[config::kPortCount]);
	//void mwm();
}

#endif