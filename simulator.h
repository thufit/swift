#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

// Sigleton simulator class
class Simulator
{
public:
	static Simulator* getSimulator();

protected:
	Simulator();

public:
	static const int nr_queue = 8;
	static const int queue_len = 100;

private:
	static Simulator * _sim;
};

Simulator* Simulator::_sim = 0;


#endif