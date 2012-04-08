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

void Schedule::maximum_match(int request[Config::nr_queue][Config::nr_queue], int grant[Config::nr_queue])
{
    int num = 0;
	n = Config::nr_queue;
	m = Config::nr_queue;

	for (int i = 0; i < Config::nr_queue; ++i)
		for (int j = 0; j < Config::nr_queue; ++j)
			map[i][j] = request[i][j];

    memset(link, -1, sizeof(link));

	cout << "map = ";
	for (int i = 0; i < Config::nr_queue; ++i)
	{
		for (int j = 0; j < Config::nr_queue; ++j)
		{
			cout << map[i][j] << ",";
		}
		cout << endl;
	}

    for (int i = 0; i < n; ++i)
    {
        memset(useif, 0, sizeof(useif));
        if (can(i))
            num++;
    }

	for (int i = 0; i < Config::nr_queue; ++i)
	{
		cout << "link[" << i << "] = " << link[i] << endl;
		if (link[i] != -1)
		{
			grant[link[i]] = i;
		}
	}
	cout << endl;

	cout << "num = " << num << endl;
}

// Parallel Iterative Matching
void Schedule::PIM(int request[Config::nr_queue][Config::nr_queue], int grant[Config::nr_queue])
{
	int matched[Config::nr_queue] = {0};
	
	vector<int> r[Config::nr_queue];
	vector<int> g[Config::nr_queue];

	// Step 1: Request
	for (int i = 0; i < Config::nr_queue; ++i)
	{
		for (int j = 0; j < Config::nr_queue; ++j)
		{
			if (request[i][j] == 1)
				g[j].push_back(i);
		}
	}

	// Step 2: Grant
	for (int i = 0; i < Config::nr_queue; ++i)
	{
		int t = Util::uniform_gen(g[i].size());
		r[g[i][t]].push_back(i);
	}

	// Step 3: Accept
	for (int i = 0; i < Config::nr_queue; ++i)
	{
		if (r[i].size() >= 1)
		{
			int t = Util::uniform_gen(r[i].size());
			grant[i] = r[i][t];
			matched[i] = 1;
		}
		else
		{
			grant[i] = -1;
		}
	}

}

void Schedule::iSLIP(int request[Config::nr_queue][Config::nr_queue], int grant[Config::nr_queue])
{
	static int grant_pointer = 0;
	static int accept_pointer = 0;

	int matched[Config::nr_queue] = {0};
	int a[Config::nr_queue][Config::nr_queue];
	int g[Config::nr_queue][Config::nr_queue];

	fill_n(&a[0][0], Config::nr_queue * Config::nr_queue, 0);
	fill_n(&g[0][0], Config::nr_queue * Config::nr_queue, 0);

	// Step 1: Request
	for (int i = 0; i < Config::nr_queue; ++i)
	{
		for (int j = 0; j < Config::nr_queue; ++j)
		{
			if (request[i][j] == 1)
				g[j][i] = 1;
		}
	}

	// Step 2: Grant
	for (int i = 0; i < Config::nr_queue; ++i)
	{
		for (int j = 0; j < Config::nr_queue; ++j)
		{
			if (g[i][grant_pointer] == 1)
			{
				a[grant_pointer][i] = 1;
				grant_pointer = (grant_pointer + 1) % Config::nr_queue;
				
				break;
			}
			grant_pointer = (grant_pointer + 1) % Config::nr_queue;
		}
	}

	// Step 3: Accept
	for (int i = 0; i < Config::nr_queue; ++i)
	{
		for (int j = 0; j < Config::nr_queue; ++j)
		{
			if (a[i][accept_pointer] == 1)
			{
				grant[i] = accept_pointer;
				accept_pointer = (accept_pointer + 1) % Config::nr_queue;
				break;
			}
			accept_pointer = (accept_pointer + 1) % Config::nr_queue;

		}

	}

}