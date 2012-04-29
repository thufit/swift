#ifndef CROSSBAR_H_
#define CROSSBAR_H_

#include "cell.h"
#include "queue.h"
#include "config.h"
#include "simulator.h"
#include "ioqueuing.h"
#include "schedule.h"

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
	void set_algorithm(schedule::Scheduling in);
	//void set_output_algorithm(schedule::OutputSchedule out);

private:
	void SetMap(int a[config::kPortCount][config::kPortCount]);

	config::QueuingType queuing_type_;
	config::TrafficModel traffic_model_;

	//IQ iq_;
	//OQ oq_;
	//VOQ voq_;

	int speedup_;
	BasicQueuing* queuing_;
	schedule::Scheduling algorithm_;
	//schedule::OutputSchedule output_algorithm_;
};

#endif
