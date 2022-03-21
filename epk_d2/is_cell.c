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

int	is_cell(agent_info_t info, int dir, cell_t type, int max)
{
	int ofs = 1;
	int temp;
	coords_t offset = offsets[dir];
	cell_t cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
	if (cell_info == type)
			return (dir);
	while (ofs <= max)
	{
		temp = dir;
		if (dir + ofs > 7)
			temp = -1;
		offset = offsets[temp + ofs];
		cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
		if (cell_info == type)
			return (temp + ofs);
		temp = dir;
		if (dir - ofs < 0)
			temp = 8;
		offset = offsets[temp - ofs];
		cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
		if (cell_info == type)
			return (temp - ofs);
		ofs++;
	}
	return (-1);
}
