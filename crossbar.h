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

class IQ
{
public:
	Queue _queue[nr_queue];
};

class OQ
{
public:
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
};

#endif
