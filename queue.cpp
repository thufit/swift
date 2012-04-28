#include "queue.h"

// Do error handling later for these functions

void Queue::push(const Cell& c)
{
	if ((end_ + 1) % Config::queue_len  == start_)
	{
		// do nothing, drop tail
	}
	else
	{
		cell_[end_] = c;
		end_ = (end_ + 1) % Config::queue_len;
	}
}

void Queue::pop()
{
	start_ = (start_ + 1) % Config::queue_len;
}

Cell& Queue::top()
{
	return cell_[start_];
}

bool Queue::empty() const
{
	return start_ == end_;
}