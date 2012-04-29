#include "ioqueuing.h"
#include "cell.h"
#include "config.h"
#include "simulator.h"
#include <iostream>

extern Stats stat;
extern Simulator* g_sim;

BasicQueuing::BasicQueuing()
{
	for (int i = 0; i < config::kPortCount; ++i)
		for (int j = 0; j < config::kPortCount; ++j)
			map_[i][j] = 0;

	for (int i = 0; i < config::kPortCount; ++i)
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
	for (int i = 0; i < config::kPortCount; ++i)
	{
		if (cell_in_[i].Empty())
			map_[i][0] = 0;
		else
		{
			map_[i][cell_in_[i].get_dest()] = 1;
		}
	}
}

void BasicQueuing::Switch(schedule::Scheduling in)
{
	schedule::MaximumMatching(map_, grant_);

	for (int i = 0; i < config::kPortCount; ++i)
	{
		if (grant_[i] != -1)
		{

			cell_out_[grant_[i]] = cell_in_[i];
			cell_in_[i].set_empty();
			std::cout << "cell" << i << "is switched to " << grant_[i] << std::endl;
		}
	}
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
	for (int i = 0; i < config::kPortCount; ++i)
		for (int j = 0; j < config::kPortCount; ++j)
			map_[i][j] = 0;

	for (int i = 0; i < config::kPortCount; ++i)
	{
		grant_[i] = -1;
	}

	for (int i = 0; i < config::kPortCount; ++i)
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

void IQ::Switch(schedule::Scheduling in)
{
	//std::cout << "...";
	switch (in)
	{
	case schedule::kiSLIP:
		schedule::iSLIP(map_, grant_);
		break;
	case schedule::kPIM:
		schedule::PIM(map_, grant_);
		break;
	case schedule::kMaximumMatching:
		schedule::MaximumMatching(map_, grant_);
	default:
		break;
	}

	for (int i = 0; i < config::kPortCount; ++i)
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
		//std::cout << "cell" << port << "is switched to " << grant_[port] << std::endl;
		stat.cell_count++;
		stat.total_delay += g_sim->get_time() - c.get_birth();
	}
}

void OQ::SetMap()
{
	//std::cout<< "...";
	for (int i = 0; i < config::kPortCount; ++i)
		for (int j = 0; j < config::kPortCount; ++j)
			map_[i][j] = 0;

	for (int i = 0; i < config::kPortCount; ++i)
	{
		grant_[i] = -1;
	}

	for (int i = 0; i < config::kPortCount; ++i)
	{
		Cell c = cell_in_[i];
		if (c.Empty())
			map_[i][0] = 0;
		else
		{
			map_[i][c.get_dest()] = 1;
			//std::cout << "adfas";
		}
	}
}

void OQ::Switch(schedule::Scheduling in)
{
	//std::cout << "...";

	switch (in)
	{
	case schedule::kiSLIP:
		schedule::iSLIP(map_, grant_);
		break;
	case schedule::kPIM:
		schedule::PIM(map_, grant_);
		break;
	case schedule::kMaximumMatching:
		schedule::MaximumMatching(map_, grant_);
	default:
		break;
	}

	for (int i = 0; i < config::kPortCount; ++i)
	{
		if (grant_[i] != -1)
		{
			Cell c = cell_in_[i];
			cell_in_[i].set_empty();
			queue_[i].Push(c);
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
	if (!cell_out_[port].Empty()) 
	{
		Cell c = cell_out_[port];
		//std::cout << "cell" << i << "is switched to " << grant_[i] << std::endl;
		stat.cell_count++;
		stat.total_delay += g_sim->get_time() - c.get_birth();
		cell_out_[port].set_empty();
	}
	//queue_[port][sequence].Pop();
}

void VOQ::SetMap()
{
		//std::cout<< "...";
	for (int i = 0; i < config::kPortCount; ++i)
		for (int j = 0; j < config::kPortCount; ++j)
			map_[i][j] = 0;

	for (int i = 0; i < config::kPortCount; ++i)
	{
		grant_[i] = -1;
	}

	for (int i = 0; i < config::kPortCount; ++i)
	{
		for (int j = 0; j < config::kPortCount; ++j)
		{
			if (!queue_[i][j].Empty())
			{
				Cell c = queue_[i][j].Top();
				map_[i][c.get_dest()] = 1;
			}
		}
	}
}
void VOQ::Switch(schedule::Scheduling in)
{
		//std::cout << "...";
	switch (in)
	{
	case schedule::kiSLIP:
		schedule::iSLIP(map_, grant_);
		break;
	case schedule::kPIM:
		schedule::PIM(map_, grant_);
		break;
	default:
		break;
	}
	
	for (int i = 0; i < config::kPortCount; ++i)
	{
		if (grant_[i] != -1)
		{
			Cell c = queue_[i][grant_[i]].Top();
			//std::cout<< "++++" << std::endl;
			cell_out_[grant_[i]] = c;
			queue_[i][c.get_dest()].Pop();
		}
	}
}