#include <iostream>
#include "cell.h"
#include "queue.h"
#include "crossbar.h"
#include "util.h"

using namespace std;

Crossbar cb;

void run()
{
#if 0
	for (int i = 0; i < 10; ++i)
	{
		cout << Util::prob_gen(0.7);

	}
#endif
	cb.nextStep();
}

int main()
{
	run();

	return 0;
}
