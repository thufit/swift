#ifndef QUEUINGMODEL_H_
#define QUEUINGMODEL_H_

#include "queue.h"
#include "schedule.h"

class BasicQueuing
{
public:
	BasicQueuing();
	//virtual ~BasicQueuing();

	virtual void Enqueue(int port, const Cell& c);
	virtual void Dequeue(int port);
	virtual void Switch();
	virtual void SetMap();

	//friend void schedule::MaximumMatching(int request[config::kPortNumber][config::kPortNumber], int grant[config::kPortNumber]);

protected:
	Cell cell_in_[config::kPortNumber];
	Cell cell_out_[config::kPortNumber];
	int map_[config::kPortNumber][config::kPortNumber];	// Request map
	int grant_[config::kPortNumber];
};

class IQ : public BasicQueuing
{
public:
	IQ();
	~IQ();
	void Enqueue(int port, const Cell& c);
	void Dequeue(int port);
	void SetMap();
	void Switch();
private:
	Queue queue_[config::kPortNumber];
};

class OQ : public BasicQueuing
{
public:
	OQ();
	~OQ();
	void Enqueue(int port, const Cell& c);
	void Dequeue(int port);
	void Switch();
private:
	Queue queue_[config::kPortNumber];	// output queue
};




class VOQ : public BasicQueuing
{
public:
	VOQ();
	~VOQ();
	void Enqueue(int port, const Cell& c);
	void Dequeue(int port);
private:
	Queue queue_[config::kPortNumber][config::kPortNumber];
};

#endif