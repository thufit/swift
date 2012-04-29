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
	virtual void Switch(schedule::Scheduling in);
	virtual void SetMap();

	//friend void schedule::MaximumMatching(int request[config::kPortCount][config::kPortCount], int grant[config::kPortCount]);

protected:
	Cell cell_in_[config::kPortCount];
	Cell cell_out_[config::kPortCount];
	int map_[config::kPortCount][config::kPortCount];	// Request map, map[i][j] == 1 means port i want to send cell to port j
	int grant_[config::kPortCount]; // 
};

class IQ : public BasicQueuing
{
public:
	IQ();
	~IQ();
	void Enqueue(int port, const Cell& c);
	void Dequeue(int port);
	void SetMap();
	void Switch(schedule::Scheduling in);
private:
	Queue queue_[config::kPortCount];
};

class OQ : public BasicQueuing
{
public:
	OQ();
	~OQ();
	void Enqueue(int port, const Cell& c);
	void Dequeue(int port);
	void SetMap();
	void Switch(schedule::Scheduling in);
private:
	Queue queue_[config::kPortCount];	// output queue
};


class VOQ : public BasicQueuing
{
public:
	VOQ();
	~VOQ();
	void Enqueue(int port, const Cell& c);
	void Dequeue(int port);
	void SetMap();
	void Switch(schedule::Scheduling in);
private:
	Queue queue_[config::kPortCount][config::kPortCount];
};

#endif