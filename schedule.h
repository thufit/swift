#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#include<cstdio>
#include<cstring>

#include "config.h"

namespace Schedule
{
	void maximum_match(int request[Config::nr_queue][Config::nr_queue], int grant[Config::nr_queue]);
	void PIM(int request[Config::nr_queue][Config::nr_queue], int grant[Config::nr_queue]);	
	void iSLIP(int request[Config::nr_queue][Config::nr_queue], int grant[Config::nr_queue]);
	void mwm();
}

#endif