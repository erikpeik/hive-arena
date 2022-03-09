#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "agent.h"

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

command_t think(agent_info_t info)
{
	static char	arr[NUM_ROWS][NUM_COLS];
	int	flower_dir;

	cell_t bee = info.cells[VIEW_DISTANCE][VIEW_DISTANCE];

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
		return (command_t) {
			.action = MOVE,
			.direction = rand() % 8
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
