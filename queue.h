#ifndef _QUEUE_H_
#define _QUEUE_H_

const int queue_len = 100;

class Queue
{
public:
	Queue() : start(0), end(0) {}

	Cell cell[queue_len];	
	int start;
	int end;
};

#endif
