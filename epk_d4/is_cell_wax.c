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

int	is_cell_wax(agent_info_t info, int dir)
{
	int ofs = 1;
	int temp;
	coords_t offset = offsets[dir];
	cell_t cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
	if (cell_info == EMPTY)
		return (dir);
	while (ofs <= 1)
	{
		temp = dir;
		if (dir + ofs > 7)
			temp = -1;
		offset = offsets[temp + ofs];
		cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
		if (cell_info == EMPTY)
			return (temp + ofs);
		temp = dir;
		if (dir - ofs < 0)
			temp = 8;
		offset = offsets[temp - ofs];
		cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
		if (cell_info == EMPTY)
			return (temp - ofs);
		ofs++;
	}

	offset = offsets[dir];
	cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
	if (cell_info == WALL)
	{
		if (dir == 0)
			return (-10);
		else
			return (-dir);
	}
	ofs = 1;
	while (ofs <= 1)
	{
		temp = dir;
		if (dir + ofs > 7)
			temp = -1;
		offset = offsets[temp + ofs];
		cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
		if (cell_info == WALL)
		{
			if (temp + ofs == 0)
				return (-10);
			else
				return (-1 * (temp + ofs));
		}
		temp = dir;
		if (dir - ofs < 0)
			temp = 8;
		offset = offsets[temp - ofs];
		cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
		if (cell_info == WALL)
		{
			if (temp - ofs == 0)
				return (-10);
			else
				return (-1 * (temp - ofs));
		}
		ofs++;
	}
	return (-11);
}
