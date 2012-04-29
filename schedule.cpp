#include <iostream>
#include <algorithm>
#include <vector>
#include "schedule.h"
#include "util.h"

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
    for (int i = 0; i < m; ++i)
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

void schedule::MaximumMatching(int request[config::kPortCount][config::kPortCount], int grant[config::kPortCount])
{
    int num = 0;
	n = config::kPortCount;
	m = config::kPortCount;

	for (int i = 0; i < config::kPortCount; ++i)
		for (int j = 0; j < config::kPortCount; ++j)
			map[i][j] = request[i][j];

    memset(link, -1, sizeof(link));

#if 0
	cout << "map = \n";
	for (int i = 0; i < config::kPortCount; ++i)
	{
		for (int j = 0; j < config::kPortCount; ++j)
		{
			cout << map[i][j] << ",";
		}
		cout << endl;
	}
#endif

    for (int i = 0; i < n; ++i)
    {
        memset(useif, 0, sizeof(useif));
        if (can(i))
            num++;
    }

	for (int i = 0; i < config::kPortCount; ++i)
	{
		//cout << "link[" << i << "] = " << link[i] << endl;
		if (link[i] != -1)
		{
			grant[link[i]] = i;
		}
	}
#if 0
	cout << endl;

	cout << "num = " << num << endl;
#endif
}

// Parallel Iterative Matching
void schedule::PIM(int request[config::kPortCount][config::kPortCount], int grant[config::kPortCount])
{
	int matched[config::kPortCount] = {0};
	
	vector<int> r[config::kPortCount];
	vector<int> g[config::kPortCount];

	// Step 1: Request
	for (int i = 0; i < config::kPortCount; ++i)
	{
		for (int j = 0; j < config::kPortCount; ++j)
		{
			if (request[i][j] == 1)
				g[j].push_back(i);
		}
	}

	// Step 2: Grant
	for (int i = 0; i < config::kPortCount; ++i)
	{
		if (!g[i].empty()){
			int t = util::Uniform(g[i].size());
			r[g[i][t]].push_back(i);
		}
	}

	// Step 3: Accept
	for (int i = 0; i < config::kPortCount; ++i)
	{
		if (r[i].size() >= 1)
		{
			int t = util::Uniform(r[i].size());
			grant[i] = r[i][t];
			matched[i] = 1;
		}
		else
		{
			grant[i] = -1;
		}
	}

}

void schedule::iSLIP(int request[config::kPortCount][config::kPortCount], int grant[config::kPortCount])
{
	static int grant_pointer = 0;
	static int accept_pointer = 0;

	int matched[config::kPortCount] = {0};
	int a[config::kPortCount][config::kPortCount];
	int g[config::kPortCount][config::kPortCount];

	fill_n(&a[0][0], config::kPortCount * config::kPortCount, 0);
	fill_n(&g[0][0], config::kPortCount * config::kPortCount, 0);

	// Step 1: Request
	for (int i = 0; i < config::kPortCount; ++i)
	{
		for (int j = 0; j < config::kPortCount; ++j)
		{
			if (request[i][j] == 1)
				g[j][i] = 1;
		}
	}

	// Step 2: Grant
	for (int i = 0; i < config::kPortCount; ++i)
	{
		for (int j = 0; j < config::kPortCount; ++j)
		{
			if (g[i][grant_pointer] == 1)
			{
				a[grant_pointer][i] = 1;
				grant_pointer = (grant_pointer + 1) % config::kPortCount;
				
				break;
			}
			grant_pointer = (grant_pointer + 1) % config::kPortCount;
		}
	}

	// Step 3: Accept
	for (int i = 0; i < config::kPortCount; ++i)
	{
		for (int j = 0; j < config::kPortCount; ++j)
		{
			if (a[i][accept_pointer] == 1)
			{
				grant[i] = accept_pointer;
				accept_pointer = (accept_pointer + 1) % config::kPortCount;
				break;
			}
			accept_pointer = (accept_pointer + 1) % config::kPortCount;

		}

	}
}