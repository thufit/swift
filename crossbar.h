#ifndef CROSSBAR_H_
#define CROSSBAR_H_

#include "cell.h"
#include "queue.h"
#include "config.h"
#include "simulator.h"



class Crossbar
{
public:
	enum QueuingType {	InputQueue, OutputQueue, VirtualOutputQueue}; // type of corssbar
	enum TrafficModel {	Bernoulli, OnOff};

	void NextStep();
	void Ingress();
	void Egress();

	void set_queuing_type(QueuingType t);
	void set_speedup(int s);
	void set_traffic_model(TrafficModel);

private:
	void SetMap(int a[Config::nr_queue][Config::nr_queue]);

	QueuingType queuing_type_;
	TrafficModel traffic_model_;
	IQ iq_;
	OQ oq_;
	VOQ voq_;
	int speedup_;

};

#endif
