#ifndef _CROSSBAR_H_
#define _CROSSBAR_H_

#include "cell.h"
#include "queue.h"
#include "config.h"

class Stat
{
public:
	int xxx;

};

struct IQ
{
	Queue _queue[nr_queue];
};

struct VOQ
{
	Queue _queue[nr_queue][nr_queue];
};

struct OQ
{
	Queue _queue[nr_queue];

};

class Crossbar
{
public:
	void nextStep();

private:
	void setMap(int a[nr_queue][nr_queue]);
	
private:
	IQ _iq;
	OQ _oq;
	VOQ _voq;
};

#endif
