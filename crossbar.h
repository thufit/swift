#ifndef _CROSSBAR_H_
#define _CROSSBAR_H_

#include "cell.h"
#include "queue.h"

class Stat
{
public:
	int xxx;

};

class IQ
{
public:
	Queue queue[nr_queue];

	const int nr_queue = 8;
};

class OQ
{

};

class Crossbar
{
public:
	IQ iq;
	
		
};

#endif
