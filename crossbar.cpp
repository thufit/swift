#include "crossbar.h"
#include "util.h"
#include "schedule.h"

const int default_cell_size = 64;
const double generating_rate = 0.5;

using namespace std;

Cell generate_cell()
{
	Cell c;
	c.birth = Util::get_current_time();
	c.size = default_cell_size;
	return c;
}

void Crossbar::nextStep()
{
	cout << " in nextStep" << endl;
	cout << "nr_queue = " << nr_queue << endl;

	for (int i = 0; i < nr_queue; ++i)
	{
		if (Util::prob_gen(generating_rate))
		{
			Cell c = generate_cell();
			c.src = i;
			c.dest = Util::uniform_gen(nr_queue);
			//_iq._queue[i].push(c);
			_voq._queue[i][c.dest].push(c);
		}
	}

	cout << "222222222222" << endl;

	int request[nr_queue][nr_queue];
	setMap(request);

	for (int i = 0; i < nr_queue; ++i)
	{
		for (int j = 0; j < nr_queue; ++j)
		{
			cout << request[i][j] << ",";
		}
		cout << endl;
	}

	int grant[nr_queue];
	for (int i = 0; i < nr_queue; ++i)
		grant[i] = -1;
	Schedule::maximum_match(request, grant);
	
	cout << "3333333" << endl;

	for (int i = 0; i < nr_queue; ++i)
	{
		if (grant[i] != -1)
		{
			// switch the cell int the input queue
			_iq._queue[i].pop();
			std::cout << "queue " << i << "poped" << std::endl; 
		}
	}
	cout << "4444444444" << endl;

	Util::time_elapse();
}

// set the request map
void Crossbar::setMap(int a[nr_queue][nr_queue])
{
	for (int i = 0; i < nr_queue; ++i)
		for (int j = 0; j < nr_queue; ++j)
			a[i][j] = 0;

	for (int i = 0; i < nr_queue; ++i)
	{
		for (int j = 0; j < nr_queue; ++j)
		{
			if (!_voq._queue[i][j].empty())
			{
				const Cell &c = _voq._queue[i][j].top();
				a[i][c.dest] = 1;
			}
		}
	}
}