#include "agent_pippuri.h"

static const coords_t offsets[] = {
	{-1, 0},
	{-1, 1},
	{ 0, 1},
	{ 1, 1},
	{ 1, 0},
	{ 1,-1},
	{ 0,-1},
	{-1,-1}
};

int	is_cell_free(agent_info_t info, int dir)
{
	int ofs = 1;
	int wax = 0;							//
	int temp;
	coords_t offset = offsets[dir];
	cell_t cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
	if (cell_info == EMPTY)
			return (dir);
	if (cell_info == WALL)					//
		wax++;								//
	while (ofs <= 2)
	{
		if (wax == 3)						//
			return (-2);					//
		temp = dir;
		if (dir + ofs > 7)
			temp = -1;
		offset = offsets[temp + ofs];
		cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
		if (cell_info == EMPTY)
			return (temp + ofs);
		if (cell_info == WALL && ofs == 1)	//
			wax++;							//
		temp = dir;
		if (dir - ofs < 0)
			temp = 8;
		offset = offsets[temp - ofs];
		cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
		if (cell_info == EMPTY)
			return (temp - ofs);
		if (cell_info == WALL && ofs == 1)	//
			wax++;							//
		ofs++;
	}
	return (-1);
}
