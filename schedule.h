#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#include<cstdio>
#include<cstring>
#include "simulator.h"

namespace Schedule
{
	void maximum_match(int request[Simulator::nr_queue][Simulator::nr_queue], int grant[Simulator::nr_queue]);
	void PIM(int request[Simulator::nr_queue][Simulator::nr_queue], int grant[Simulator::nr_queue]);	
	void iSLIP(int request[Simulator::nr_queue][Simulator::nr_queue], int grant[Simulator::nr_queue]);
	void mwm();
}

#endif