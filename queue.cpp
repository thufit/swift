#include "queue.h"

// Do error handling later for these functions

void Queue::push(const Cell& c)
{
	if ((_end + 1) % Config::queue_len  == _start)
	{
		// do nothing, drop tail
	}
	else
	{
		_cell[_end] = c;
		_end = (_end + 1) % Config::queue_len;
	}
}

void Queue::pop()
{
	_start = (_start + 1) % Config::queue_len;
}

Cell& Queue::top()
{
	return _cell[_start];
}

bool Queue::empty() const
{
	return _start == _end;
}