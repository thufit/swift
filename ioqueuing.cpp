#include "ioqueuing.h"
#include "cell.h"
#include "config.h"
#include "simulator.h"
#include <iostream>

extern Stats stat;
extern Simulator* g_sim;

BasicQueuing::BasicQueuing()
{
	for (int i = 0; i < config::kPortNumber; ++i)
		for (int j = 0; j < config::kPortNumber; ++j)
			map_[i][j] = 0;

	for (int i = 0; i < config::kPortNumber; ++i)
	{
		grant_[i] = -1;
	}
}

void BasicQueuing::Enqueue(int port, const Cell& c)
{
	cell_in_[port] = c;
}

void BasicQueuing::Dequeue(int port)
{
	cell_in_[port].set_empty();
}

void BasicQueuing::SetMap()
{
	for (int i = 0; i < config::kPortNumber; ++i)
	{
		if (cell_in_[i].Empty())
			map_[i][0] = 0;
		else
		{
			map_[i][cell_in_[i].get_dest()] = 1;
		}
	}
}

void BasicQueuing::Switch()
{
	schedule::MaximumMatching(map_, grant_);

	for (int i = 0; i < config::kPortNumber; ++i)
	{
		if (grant_[i] != -1)
		{

			cell_out_[grant_[i]] = cell_in_[i];
			cell_in_[i].set_empty();
			std::cout << "cell" << i << "is switched to " << grant_[i] << std::endl;
		}
	}
}


VOQ::VOQ()
{
}

VOQ::~VOQ()
{
}

void VOQ::Enqueue(int port, const Cell& c)
{
	queue_[port][c.get_dest()].Push(c);
}

void VOQ::Dequeue(int port)
{
	//queue_[port][sequence].Pop();
}


IQ::IQ()
{
}

IQ::~IQ()
{
}

void IQ::Enqueue(int port, const Cell& c)
{
	queue_[port].Push(c);
}

void IQ::Dequeue(int port)
{
	if (!cell_out_[port].Empty()) 
	{
		Cell c = cell_out_[port];
		//std::cout << "cell" << i << "is switched to " << grant_[i] << std::endl;
		stat.cell_count++;
		stat.total_delay += g_sim->get_time() - c.get_birth();
		cell_out_[port].set_empty();
	}
}

void IQ::SetMap()
{
	//std::cout<< "...";
	for (int i = 0; i < config::kPortNumber; ++i)
		for (int j = 0; j < config::kPortNumber; ++j)
			map_[i][j] = 0;

	for (int i = 0; i < config::kPortNumber; ++i)
	{
		grant_[i] = -1;
	}

	for (int i = 0; i < config::kPortNumber; ++i)
	{
		if (queue_[i].Empty())
			map_[i][0] = 0;
		else
		{
			map_[i][queue_[i].Top().get_dest()] = 1;
			//std::cout << "adfas";
		}
	}
}

void IQ::Switch()
{
	//std::cout << "...";
	schedule::MaximumMatching(map_, grant_);

	for (int i = 0; i < config::kPortNumber; ++i)
	{
		if (grant_[i] != -1)
		{
			Cell c = queue_[i].Top();
			//std::cout<< "++++" << std::endl;
			cell_out_[grant_[i]] = c;
			queue_[i].Pop();

		}
	}
}

OQ::OQ()
{
}

OQ::~OQ()
{
}

void OQ::Enqueue(int port, const Cell& c)
{
	cell_in_[port] = c;
	//queue_[port].Push(c);
}

void OQ::Dequeue(int port)
{
	if (!queue_[port].Empty())
	{
		// add scheduling algorithm here, like QoS

		Cell c = queue_[port].Top();
		queue_[port].Pop();
		//std::cout << "cell" << i << "is switched to " << grant_[i] << std::endl;
		stat.cell_count++;
		stat.total_delay += g_sim->get_time() - c.get_birth();
	}
}

void OQ::Switch()
{
	//std::cout << "...";
	schedule::MaximumMatching(map_, grant_);

	for (int i = 0; i < config::kPortNumber; ++i)
	{
		if (grant_[i] != -1)
		{
			Cell c = cell_in_[i];
			cell_in_[i].set_empty();
			queue_[i].Push(c);
		}
	}
}
