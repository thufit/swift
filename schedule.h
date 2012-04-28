#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include<cstdio>
#include<cstring>

#include "config.h"

namespace schedule
{
	void MaximumMatching(int request[config::kPortNumber][config::kPortNumber], int grant[config::kPortNumber]);
	void PIM(int request[config::kPortNumber][config::kPortNumber], int grant[config::kPortNumber]);	
	void iSLIP(int request[config::kPortNumber][config::kPortNumber], int grant[config::kPortNumber]);
	void mwm();
}

#endif