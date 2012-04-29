#include "crossbar.h"
#include "util.h"
#include "schedule.h"
#include "traffic.h"
#include "simulator.h"


using namespace std;
extern Simulator* g_sim;

Cell generate_cell()
{
	Cell c;
	c.set_birth(g_sim->get_time());
	c.set_size(config::kDefaultCellSize);
	return c;
}


Crossbar::Crossbar()
{
	queuing_ = NULL;
}

Crossbar::~Crossbar()
{
	delete queuing_;
}

void Crossbar::NextStep()
{

	//cout << " in nextStep" << endl;
	//cout << "kQueueNumber = " << config::kQueueNumber << endl;


	//for (int i = 0; i < config::kQueueNumber; ++i)
	//{
	//	if (Util::Probability(config::Rate))
	//	{
	//		Cell c = generate_cell();
	//		c.set_src(i);
	//		c.set_dest(Util::Uniform(config::kQueueNumber));
	//		//_iq._queue[i].Push(c);
	//		_voq._queue[i][c.get_dest()].Push(c);
	//	}
	//}
	//cout << "222222222222" << endl;

#if 0
	int request[config::kPortCount][config::kPortCount];
	SetMap(request);
#endif

	//for (int i = 0; i < config::kQueueNumber; ++i)
	//{
	//	for (int j = 0; j < config::kQueueNumber; ++j)
	//	{
	//		cout << request[i][j] << ",";
	//	}
	//	cout << endl;
	//}

#if 0
	int grant[config::kPortCount];
	for (int i = 0; i < config::kPortCount; ++i)
		grant[i] = -1;
	schedule::MaximumMatching(request, grant);
#endif

	if (queuing_type_ == config::kInputQueuing)
	{
		//queuing_->
	}
	else
	{
	}
	
	//cout << "3333333" << endl;
#if 0
	for (int i = 0; i < config::kQueueNumber; ++i)
	{
		if (grant[i] != -1)
		{
			// switch the cell into the input queue
#if 0
			iq_.queue_[i].Pop();
#else
			queuing_->Dequeue(i);
#endif
			//std::cout << "queue " << i << "poped" << std::endl; 
		}
	}
#endif

	for (int i = 0; i < speedup_; ++i)
	{
		queuing_->SetMap();
		queuing_->Switch(algorithm_);
	}
}

#if 0
// set the request map
void Crossbar::SetMap(int a[config::kPortCount][config::kPortCount])
{
	for (int i = 0; i < config::kPortCount; ++i)
		for (int j = 0; j < config::kPortCount; ++j)
			a[i][j] = 0;

	for (int i = 0; i < config::kPortCount; ++i)
	{
		for (int j = 0; j < config::kPortCount; ++j)
		{
			if (!voq_.queue_[i][j].Empty())
			{
				const Cell &c = voq_.queue_[i][j].Top();
				a[i][c.get_dest()] = 1;
			}
		}
	}
}
#endif

// ingress cells into the input buffers(queues) of crossbar
void Crossbar::Ingress()
{
	// generation and insertion
	vector<Cell> vc(config::kPortCount);
	traffic::Bernoulli(vc, config::Rate);

	//cout << "in Ingress" << endl;
#if 0
	for (int i = 0; i < (int)vc.size(); ++i)
	{
		Cell& c = vc[i];
		if (!c.Empty())
		{
			voq_.queue_[i][c.get_dest()].Push(c);
		}
	}
#else
	for (int i = 0; i < (int)vc.size(); ++i)
	{
		Cell& c = vc[i];
		if (!c.Empty())
		{
			queuing_->Enqueue(i, c);
			//cout << "input a cell\n"; 
		}
	}
#endif
}

void Crossbar::Egress()
{
	for (int i = 0; i < config::kPortCount; ++i)
	{
		queuing_->Dequeue(i);
	}
}

void Crossbar::set_queuing_type(config::QueuingType t)
{
	queuing_type_ = t;

	switch (t)
	{
	case config::kInputQueuing:
		queuing_ = new IQ();
		break;
	case config::kOutputQueuing:
		queuing_ = new OQ();
		break;
	case config::kVirtualOutputQueuing:
		queuing_ = new VOQ();
		break;
	default:
		break;
	}
}

void Crossbar::set_speedup(int s)
{
	speedup_ = s;
}

void Crossbar::set_traffic_model(config::TrafficModel t)
{
	traffic_model_ = t;
}

void Crossbar::set_algorithm(schedule::Scheduling in)
{
	algorithm_ = in;
}

//void Crossbar::set_output_algorithm(schedule::OutputSchedule out)
//{
//	output_algorithm_ = out;
//}