#include "schedule.h"

using namespace std;

static const int N = 1024;
static int map[N][N];
static int link[N];
static int useif[N];
static int n, m;

//
// Hungarian algorithm for maximum matchings in bipartite graphs,
// the complexity of this algorithm is O(mn).
// (where m is the number of edges and n is number of nodes in the left side)
//

static bool can(int t)
{
    for (int i = 0; i < m; i++)
    {
        if (useif[i] == 0 && map[t][i])
        {
            useif[i] = 1;
            if (link[i] == -1 || can(link[i]))
            {
                link[i] = t;
                return true;
            }
        }
    }

    return false;
}

void Schedule::maximum_match(int request[nr_queue][nr_queue], int grant[nr_queue])
{
    int num = 0;
    memset(link, -1, sizeof(link));
    for (int i = 0; i < n; i++)
    {
        memset(useif, 0, sizeof(useif));
        if (can(i))
            num++;
    }

	for (int i = 0; i < nr_queue; ++i)
	{
		if (link[i] != -1)
		{
			grant[link[i]] = i;
		}
	}
}