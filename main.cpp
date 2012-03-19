#include <iostream>
#include "cell.h"
#include "queue.h"
#include "crossbar.h"
#include "util.h"

using namespace std;

Crossbar cb;

void run()
{
	for (int i = 0; i < 10; ++i)
	{
		cout << Util::prob_gen(0.7);

	}
}

int main()
{
	run();

	return 0;
}
