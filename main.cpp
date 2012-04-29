#include <iostream>
#include "cell.h"
#include "queue.h"
#include "crossbar.h"
#include "util.h"
#include "simulator.h"
#include "config.h"
#include "traffic.h"

using namespace std;

Stats stat;
Simulator* g_sim = 0;

void RunInputQueuing()
{

//#if 0
//	for (int i = 0; i < 10; ++i)
//	{
//		cout << Util::Probability(0.7);
//
//	}
//#endif
	
	Crossbar cb;
	cb.set_queuing_type(config::kInputQueuing);
	cb.set_speedup(1);	// no speedup
	cb.set_traffic_model(config::kBernoulli);

	for (double p = 0; p <=1; p += 0.1)
	{
		cout << "p = " << p << endl;
		config::Rate = p;

		for (int i = 0; i < 1000; ++i)
		{
			//cout << "i = " << i << endl;

			cb.Egress();
			cb.NextStep();
			cb.Ingress();

			g_sim->Elapse();
		}


		cout << "cell count = " << stat.cell_count << endl
			<< "average delay = " << stat.total_delay / stat.cell_count << endl;
	}
}

void RunOutputQueuing()
{
	Crossbar cb;
	cb.set_queuing_type(config::kOutputQueuing);
	cb.set_speedup(config::kPortCount);	// speedup n
	cb.set_traffic_model(config::kBernoulli);

#if 1
	for (double p = 0; p <= 1; p += 0.1)
	{
		cout << "p = " << p << endl;
		config::Rate = p;

		for (int i = 0; i < 1000; ++i)
		{
			//cout << "i = " << i << endl;

			cb.Egress();
			cb.NextStep();
			cb.Ingress();


			g_sim->Elapse();
		}


		cout << "cell count = " << stat.cell_count << endl
			<< "average delay = " << stat.total_delay / stat.cell_count << endl;
	}
#else
	double p = .5;
	cout << "p = " << p << endl;
	config::Rate = p;

	for (int i = 0; i < 1000; ++i)
	{
		//cout << "i = " << i << endl;

		cb.Egress();
		cb.NextStep();
		cb.Ingress();


		g_sim->Elapse();
	}

#endif

}

void RunVOQ(schedule::Scheduling in)
{
	Crossbar cb;
	cb.set_queuing_type(config::kVirtualOutputQueuing);
	cb.set_speedup(1);	// speedup n
	cb.set_traffic_model(config::kBernoulli);
	cb.set_algorithm(in);

#if 1
	for (double p = 0; p <= 1; p += 0.1)
	{
		cout << "p = " << p << endl;
		config::Rate = p;

		for (int i = 0; i < config::sim_duration; ++i)
		{
			//cout << "i = " << i << endl;

			cb.Egress();
			cb.NextStep();
			cb.Ingress();

			g_sim->Elapse();
		}


		cout << "cell count = " << stat.cell_count << endl
			<< "average delay = " << stat.total_delay / stat.cell_count << endl;
	}
#else
	config::Rate = 0.5;
	
	cb.Ingress();
	cb.NextStep();
	cb.Egress();

	g_sim->Elapse();

#endif
}

void init()
{
	g_sim = Simulator::GetSimulator();
}

int main()
{
	init();
	//RunInputQueuing();
	//RunOutputQueuing();
	RunVOQ(schedule::kiSLIP);

#if 0
	for (int i = 0; i < 10; ++i)
	{
		cout << util::Uniform(1);
	}
#endif


#if 0
	Queue q;

	for (int i = 0; i < 5; ++i)
	{
		Cell c;
		q.Push(c);
				std::cout << q.Length() << endl;
	}
	q.Pop();
	std::cout << q.Length() << std::endl;
		for (int i = 0; i < 5; ++i)
	{
		Cell c;
		q.Push(c);
				std::cout << q.Length() << endl;
	}
#endif
	return 0;
}
