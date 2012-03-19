#ifndef _CELL_H_
#define _CELL_H_

struct Cell
{
	Cell() : src(0), dest(0), size(0), birth(0), death(0) {}

	int src;
	int dest;
	int size;
	int birth;
	int death;
};

#endif
