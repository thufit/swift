#include "crossbar.h"
#include "util.h"
#include "schedule.h"

const int default_cell_size = 64;
const double generating_rate = 0.5;

Cell generate_cell()
{
	Cell c;
	c.birth = Util::get_current_time();
	c.size = default_cell_size;
	return c;
}

void Crossbar::nextStep()
{
	for (int i = 0; i < nr_queue; ++i)
	{
		if (Util::prob_gen(generating_rate))
		{
			Cell c = generate_cell();
			c.src = i;
			c.dest = Util::uniform_gen(nr_queue);
			_iq._queue[i].push(c);
		}
	}
	
	int request[nr_queue][nr_queue];
	setMap(request);
	int grant[nr_queue];
	for (int i = 0; i < nr_queue; ++i)
		grant[i] = -1;
	Schedule::maximum_match(request, grant);

	Util::time_elapse();
}

// 
void Crossbar::setMap(int a[nr_queue][nr_queue])
{
	for (int i = 0; i < nr_queue; ++i)
		for (int j = 0; j < nr_queue; ++i)
			a[i][j] = 0;

	for (int i = 0; i < nr_queue; ++i)
	{
		if (!_iq._queue[i].empty())
		{
			const Cell &c = _iq._queue[i].top();
			a[i][c.dest] = 1;
			a[c.dest][i] = 1;
		}
	}
}