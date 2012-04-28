#ifndef QUEUE_H_
#define QUEUE_H_

#include "cell.h"
#include "config.h"

class Queue
{
public:
	Queue() : start_(0), end_(0) {}
	void Push(const Cell&);
	void Pop();
	Cell& Top();
	bool Empty() const;
	int Length() const;

private:		
	Cell cell_[config::kQueueLength];	
	int start_;
	int end_;
};


#endif
