#ifndef QUEUE_H_
#define QUEUE_H_

#include "cell.h"
#include "config.h"

class Queue
{
public:
	Queue() : start_(0), end_(0) {}
	void push(const Cell&);
	void pop();
	Cell& top();
	bool empty() const;

private:		
	Cell cell_[Config::queue_len];	
	int start_;
	int end_;

};


struct IQ
{
	Queue queue_[Config::nr_queue];
};

struct VOQ
{
	Queue queue_[Config::nr_queue][Config::nr_queue];
};

struct OQ
{
	Queue queue_[Config::nr_queue];

};

#endif
