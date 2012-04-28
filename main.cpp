#include <iostream>
#include "cell.h"
#include "queue.h"
#include "crossbar.h"
#include "util.h"
#include "simulator.h"

using namespace std;

Stats stat;
Simulator* g_sim = 0;

void RunInputQueuing()
{

//#if 0
//	for (int i = 0; i < 10; ++i)
//	{
//		cout << Util::GenerateWithProbability(0.7);
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
		config::GeneratingRate = p;

		for (int i = 0; i < 1000; ++i)
		{
			//cout << "i = " << i << endl;
			cb.Ingress();
			cb.NextStep();
			g_sim->Elapse();
		}


		cout << "cell count = " << stat.cell_count << endl
			<< "average delay = " << stat.total_delay / stat.cell_count << endl;
	}
}

void RunOutputQueuing()
{


}

void init()
{
	g_sim = Simulator::GetSimulator();
}

int main()
{
	init();
	RunInputQueuing();


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
