#ifndef _CROSSBAR_H_
#define _CROSSBAR_H_

#include "cell.h"
#include "queue.h"
#include "config.h"
#include "simulator.h"

class Stat
{
public:
	int xxx;

};

struct IQ
{
	Queue _queue[Config::nr_queue];
};

struct VOQ
{
	Queue _queue[Config::nr_queue][Config::nr_queue];
};

struct OQ
{
	Queue _queue[Config::nr_queue];

};

class Crossbar
{
public:
	enum toc {InputQueue, OutputQueue, VirtualOutputQueue}; // type of corssbar

public:
	void nextStep();
	void ingress();
	void egress();
	void setType(toc t);
	void setSpeedup(int s);

private:
	void setMap(int a[Config::nr_queue][Config::nr_queue]);

	
private:

	toc type;
	IQ _iq;
	OQ _oq;
	VOQ _voq;
	int _speedup;

};

#endif
