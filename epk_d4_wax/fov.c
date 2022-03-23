#include "agent_pippuri.h"

static const coords_t se_offsets[] = {
	{-3, 0},
    {-3, 1},
	{-3, 2},
	{-3, 3},
	{-2, 3},
	{-1, 3},
	{0, 3},
	{1, 3},
	{2, 3},
	{3, 3},
	{3, 2},
	{3, 1},
	{3, 0},
	{3, -1},
	{3, -2},
	{3, -3},
	{2, -3},
	{1, -3},
	{0, -3},
	{-1, -3},
	{-2, -3},
	{-3, -3},
	{-3, -2},
	{-3, -1},
};

static const coords_t e_offsets[] = {
	{-2, 0}, // 0
	{-2, 1}, // 1
	{-2, 2}, // 2
	{-1, 2}, // 3
	{0, 2},
	{1, 2},
	{2, 2},
	{2, 1},
	{2, 0},
	{2, -1},
	{2, -2},
	{1, -2},
	{0, -2},
	{-1, -2},
	{-2, -2},
	{-2, -1}
};

coords_t direction_to_coords_3(coords_t from, int direction)
{
	coords_t offset = se_offsets[direction];

	return (coords_t) {
		.row = from.row + offset.row,
		.col = from.col + offset.col
	};
}

coords_t direction_to_coords_2(coords_t from, int direction)
{
	coords_t offset = e_offsets[direction];

	return (coords_t) {
		.row = from.row + offset.row,
		.col = from.col + offset.col
	};
}

int	find_distant(agent_info_t info, cell_t type, coords_t targets[5])
{
	coords_t center = {VIEW_DISTANCE, VIEW_DISTANCE};
	int	is_targeted	= 0;
	int	i;

	for (int dir = 0 ; dir < 16 ; dir++)
	{
		coords_t coords = direction_to_coords_2(center, dir);
		cell_t distant = info.cells[coords.row][coords.col];
		if (type == FLOWER && distant == FLOWER)
		{
			i = 0;
			while (i < 5)
			{
				if (targets[i].row == coords.row + info.row - VIEW_DISTANCE && targets[i].col == coords.col + info.col - VIEW_DISTANCE)
				{
					is_targeted = 1;
					break ;
				}
				i++;
			}
			if (is_targeted == 0)
			{
				targets[info.bee].row = coords.row + info.row - VIEW_DISTANCE;
				targets[info.bee].col = coords.col + info.col- VIEW_DISTANCE;
			}
			else
			{
				is_targeted = 0;
				continue ;
			}
		}
		if (distant == type)
			return (dir/2);
	}
    	for (int dir = 0 ; dir < 24 ; dir++)
	{
		coords_t coords = direction_to_coords_3(center, dir);
		cell_t distant = info.cells[coords.row][coords.col];
		if (type == FLOWER && distant == FLOWER)
		{
			i = 0;
			while (i < 5)
			{
				if (targets[i].row == coords.row + info.row - VIEW_DISTANCE && targets[i].col == coords.col + info.col - VIEW_DISTANCE)
				{
					is_targeted = 1;
					break ;
				}
				i++;
			}
			if (is_targeted == 0)
			{
				targets[info.bee].row = coords.row + info.row - VIEW_DISTANCE;
				targets[info.bee].col = coords.col + info.col - VIEW_DISTANCE;
			}
			else
			{
				is_targeted = 0;
				continue ;
			}
		}
		if (distant == type)
			return (dir/3);
	}
	return (-11);
}

int find_neighbour(agent_info_t info, cell_t type)
{
	coords_t center = {VIEW_DISTANCE, VIEW_DISTANCE};

	for(int dir = 0 ; dir < 8 ; dir++)
	{
		coords_t coords = direction_to_coords(center, dir);
		cell_t neighbour = info.cells[coords.row][coords.col];
		if (neighbour == type)
		{
			return dir;
		}
	}
	return (-11);
}
