#include "queue.h"
#include <cassert>

// Do error handling later for these functions

void Queue::Push(const Cell& c)
{
	if ((end_ + 1) % config::kQueueLength  == start_)
	{
		// do nothing, drop tail
		assert(0); // full
	}
	else
	{
		cell_[end_] = c;
		end_ = (end_ + 1) % config::kQueueLength;
	}
}

void Queue::Pop()
{
	assert(!this->Empty());

	start_ = (start_ + 1) % config::kQueueLength;
}

Cell& Queue::Top()
{
	assert(!this->Empty());
	return cell_[start_];
}

bool Queue::Empty() const
{
	return start_ == end_;
}

int Queue::Length() const
{
	int len = 0;

	if (end_ > start_)
		len = end_ - start_;
	else
		len = config::kQueueLength - (start_ - end_);

	return len;		
}

