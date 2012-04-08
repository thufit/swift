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
	void nextStep();
	void ingress();
	void egress();

private:
	void setMap(int a[Config::nr_queue][Config::nr_queue]);
	
private:
	enum toc {IQ, OQ, VOQ}; // type of corssbar
	IQ _iq;
	OQ _oq;
	VOQ _voq;
};

#endif
