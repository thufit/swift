#include "queue.h"

// Do error handling later for these functions

void Queue::push(const Cell& c)
{
	if ((end + 1) % queue_len  == start)
	{
		// do nothing, drop tail
	}
	else
	{
		cell[end] = c;
		end = (end + 1) % queue_len;
	}
}

void Queue::pop()
{
	start = (start + 1) % queue_len;
}