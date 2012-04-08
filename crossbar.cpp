#include "crossbar.h"
#include "util.h"
#include "schedule.h"
#include "traffic.h"


using namespace std;

Cell generate_cell()
{
	Cell c;
	c.setBirth(Util::get_current_time());
	c.setSize(Config::default_cell_size);
	return c;
}

void Crossbar::nextStep()
{
	cout << " in nextStep" << endl;
	cout << "nr_queue = " << Config::nr_queue << endl;

#if 0
	for (int i = 0; i < Config::nr_queue; ++i)
	{
		if (Util::prob_gen(Config::generating_rate))
		{
			Cell c = generate_cell();
			c.setSrc(i);
			c.setDest(Util::uniform_gen(Config::nr_queue));
			//_iq._queue[i].push(c);
			_voq._queue[i][c.getDest()].push(c);
		}
	}

#endif



	cout << "222222222222" << endl;

	int request[Config::nr_queue][Config::nr_queue];
	setMap(request);

	for (int i = 0; i < Config::nr_queue; ++i)
	{
		for (int j = 0; j < Config::nr_queue; ++j)
		{
			cout << request[i][j] << ",";
		}
		cout << endl;
	}

	int grant[Config::nr_queue];
	for (int i = 0; i < Config::nr_queue; ++i)
		grant[i] = -1;
	Schedule::maximum_match(request, grant);
	
	cout << "3333333" << endl;

	for (int i = 0; i < Config::nr_queue; ++i)
	{
		if (grant[i] != -1)
		{
			// switch the cell int the input queue
			_iq._queue[i].pop();
			std::cout << "queue " << i << "poped" << std::endl; 
		}
	}
	cout << "4444444444" << endl;

	//Util::time_elapse();
}

// set the request map
void Crossbar::setMap(int a[Config::nr_queue][Config::nr_queue])
{
	for (int i = 0; i < Config::nr_queue; ++i)
		for (int j = 0; j < Config::nr_queue; ++j)
			a[i][j] = 0;

	for (int i = 0; i < Config::nr_queue; ++i)
	{
		for (int j = 0; j < Config::nr_queue; ++j)
		{
			if (!_voq._queue[i][j].empty())
			{
				const Cell &c = _voq._queue[i][j].top();
				a[i][c.getDest()] = 1;
			}
		}
	}
}

// ingress cells into the input buffers(queues) of crossbar
void Crossbar::ingress()
{
	// generation and insertion
	vector<Cell> vc(Config::nr_queue);
	Traffic::BernoulliDistribution(vc, Config::generating_rate);

	for (int i = 0; i < (int)vc.size(); ++i)
	{
		Cell& c = vc[i];
		if (!c.empty())
		{
			_voq._queue[i][c.getDest()].push(c);
		}
	}

}

void Crossbar::egress()
{

}