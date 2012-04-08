#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

// Sigleton simulator class
class Simulator
{
public:
	static Simulator* getSimulator();
	static void elaspe();
	static long getTime();

protected:
	Simulator();

private:
	static Simulator * _sim;
	static long _time;
};


#endif