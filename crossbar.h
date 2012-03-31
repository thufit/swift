#ifndef _CROSSBAR_H_
#define _CROSSBAR_H_

#include "cell.h"
#include "queue.h"
#include "simulator.h"

class Stat
{
public:
	int xxx;

};

struct IQ
{
	Queue _queue[Simulator::nr_queue];
};

struct VOQ
{
	Queue _queue[Simulator::nr_queue][Simulator::nr_queue];
};

struct OQ
{
	Queue _queue[Simulator::nr_queue];

};

class Crossbar
{
public:
	void nextStep();

private:
	void setMap(int a[Simulator::nr_queue][Simulator::nr_queue]);
	void ingress();
	void egress();
	
private:
	IQ _iq;
	OQ _oq;
	VOQ _voq;
};

#endif
