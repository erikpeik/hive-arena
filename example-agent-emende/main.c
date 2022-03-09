#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "agent.h"

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

int	find_distant(agent_info_t info, cell_t type)
{
	coords_t center = {VIEW_DISTANCE, VIEW_DISTANCE};

	for (int dir = 0 ; dir < 16 ; dir++)
	{
		coords_t coords = direction_to_coords_2(center, dir);
		cell_t distant = info.cells[coords.row][coords.col];
		if (distant == type)
			return (dir/2);
	}
    	for (int dir = 0 ; dir < 24 ; dir++)
	{
		coords_t coords = direction_to_coords_3(center, dir);
		cell_t distant = info.cells[coords.row][coords.col];
		if (distant == type)
			return (dir/3);
	}
	return (-1);
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
	return -1;
}

int	return_to_hive(agent_info_t info, coords_t hive_loc)
{
	if (info.col > hive_loc.col)
	{
		if (info.row > hive_loc.row)
			return (7);
		else if (info.row < hive_loc.row)
			return (5);
		else
			return (6);
	}
	else if (info.col < hive_loc.col)
	{
		if (info.row > hive_loc.row)
			return (1);
		else if (info.row < hive_loc.row)
			return (3);
		else
			return (2);
	}
	else
	{
		if (info.row > hive_loc.row)
			return (0);
		else
			return (4);
	}
}

command_t think(agent_info_t info)
{
	static char	arr[NUM_ROWS][NUM_COLS];
	int	flower_dir;
	coords_t hive_loc;

	cell_t bee = info.cells[VIEW_DISTANCE][VIEW_DISTANCE];
	if (info.player == 0)
	{
		hive_loc.row = (NUM_ROWS / 2);
		hive_loc.col = 1;
	}
	else
	{
		hive_loc.row = (NUM_ROWS / 2);
		hive_loc.col = (NUM_COLS - 2);
	}
	if (is_bee_with_flower(bee))
	{
		int	hive_dir = find_neighbour(info, hive_cell(info.player));
		if (hive_dir >= 0)
		{
			return (command_t) {
				.action = FORAGE,
				.direction = hive_dir
			};
		}
		hive_dir = return_to_hive(info, hive_loc);
		return (command_t) {
			.action = MOVE,
			.direction = hive_dir
		};
	}
	else
	{
		flower_dir = find_neighbour(info, FLOWER);
		if (flower_dir >= 0)
		{
			return (command_t) {
				.action = FORAGE,
				.direction = flower_dir
			};
		}
		flower_dir = find_distant(info, FLOWER);
		if (flower_dir >= 0)
		{
			return (command_t) {
				.action = MOVE,
				.direction = flower_dir
			};
		}
		return (command_t) {
			.action = MOVE,
			.direction = rand() % 8
		};
	}
/*	return (command_t) {
		.action = MOVE,
		.direction = rand() % 8
	}; */
}

int main(int argc, char **argv)
{
	if (argc < 3)
		panic("Usage: ./agent arena_host arena_ip");

	srand(time(NULL) + getpid());

	char *host = argv[1];
	int port = atoi(argv[2]);
	char *team_name = "Eerikin Pippuri Kebab";

	agent_main(host, port, team_name, think);
}
