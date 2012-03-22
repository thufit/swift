#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#include<cstdio>
#include<cstring>
#include "config.h"

namespace Schedule
{
	void maximum_match(int request[nr_queue][nr_queue], int grant[nr_queue]);
	void PIM(int request[nr_queue][nr_queue], int grant[nr_queue]);	
	void iSLIP(int request[nr_queue][nr_queue], int grant[nr_queue]);
	void mwm();
}

#endif