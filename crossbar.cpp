#include "crossbar.h"
#include "util.h"

const int default_cell_size = 64;
const double generating_rate = 0.5;

Cell generate_cell()
{
	Cell c;
	c.birth = Util::get_current_time();
	c.size = default_cell_size;
	return c;
}

void Crossbar::next_step()
{
	for (int i = 0; i < nr_queue; ++i)
	{
		if (Util::prob_gen(generating_rate))
		{
			Cell c = generate_cell();
			c.src = i;
			c.dest = Util::uniform_gen(nr_queue);
			iq.queue[i].push(c);
		}
	}


	Util::time_elapse();
}