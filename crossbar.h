#ifndef CROSSBAR_H_
#define CROSSBAR_H_

#include "cell.h"
#include "queue.h"
#include "config.h"
#include "simulator.h"
#include "queuingmodel.h"

class Crossbar
{
public:
	Crossbar();
	~Crossbar();

	void NextStep();
	void Ingress();
	void Egress();

	void set_queuing_type(config::QueuingType t);
	void set_speedup(int s);
	void set_traffic_model(config::TrafficModel tm);

private:
	void SetMap(int a[config::kQueueNumber][config::kQueueNumber]);

	config::QueuingType queuing_type_;
	config::TrafficModel traffic_model_;

	//IQ iq_;
	//OQ oq_;
	//VOQ voq_;

	int speedup_;
	BasicQueuing* queuing_;
};

#endif
