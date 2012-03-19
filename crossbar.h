#ifndef _CROSSBAR_H_
#define _CROSSBAR_H_

#include "cell.h"
#include "queue.h"

const int nr_queue = 8;

class Stat
{
public:
	int xxx;

};

class IQ
{
public:
	Queue queue[nr_queue];
};

class OQ
{
public:
	Queue queue[nr_queue];


};

class Crossbar
{
public:
	void next_step();

private:
	IQ iq;
	OQ oq;
};

#endif
