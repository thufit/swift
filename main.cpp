#include <iostream>
#include "cell.h"
#include "queue.h"
#include "crossbar.h"
#include "util.h"
#include "simulator.h"

using namespace std;

Crossbar cb;
Simulator* sim = 0;

void run()
{
#if 0
	for (int i = 0; i < 10; ++i)
	{
		cout << Util::prob_gen(0.7);

	}
#endif
	
	cb.set_queuing_type(Crossbar::InputQueue);
	cb.set_speedup(1);	// no speedup
	cb.set_traffic_model(Crossbar::Bernoulli);

	cb.NextStep();
	sim->elaspe();

}

void init()
{
	sim = Simulator::getSimulator();
}



int main()
{
	init();
	run();

	return 0;
}
