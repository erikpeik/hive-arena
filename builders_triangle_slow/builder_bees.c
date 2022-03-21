#include "agent_pippuri.h"

int toggle = 1;

command_t	builder_bees(agent_info_t info,  coords_t hive_loc)
{
	int	spy_dir, temp, flower_dir, enemy_dir;
	coords_t	spy_loc;
	command_t	result;

	if (toggle == 1)
	{
		if (info.bee == 0)
		{
			if (info.player == 0)
				spy_loc.col = 3;
			else
				spy_loc.col = 26;
			spy_loc.row = 3;
		}
		if (info.bee == 4)
		{
			if (info.player == 0)
				spy_loc.col = 3;
			else
				spy_loc.col = 26;
			spy_loc.row = 26;
		}
		if (info.row == spy_loc.row)
			toggle = 0;
	}
	if (toggle == 0)
	{
		if (info.bee == 0)
		{
			if (hive_loc.col > (NUM_COLS / 2))
				spy_loc.col = 1;
			else
				spy_loc.col = 28;
			spy_loc.row = 11;
		}
		if (info.bee == 4)
		{
			if (hive_loc.col > (NUM_COLS / 2))
				spy_loc.col = 1;
			else
				spy_loc.col = 28;
			spy_loc.row = 13;
		}
	}
	if (info.col != spy_loc.col)
	{
		spy_dir = return_to_hive(info, spy_loc);
		temp = spy_dir;
		spy_dir = is_cell_wax(info, spy_dir);
		if (spy_dir >= 0)
		{
			return (command_t) {
				.action = MOVE,
				.direction = spy_dir
			};
		}
		/* Breaking the WALL */
		if (spy_dir < 0)
		{
			if (spy_dir == -11)
			{
				/* Move random direction */
				return (command_t) {
					.action = MOVE,
					.direction = rand() % 8
				};
			}
			if (spy_dir == -10)
				spy_dir = 0;
			else
				spy_dir = spy_dir * -1;
			return (command_t) {
				.action = GUARD,
				.direction = spy_dir
			};
		}
	}
	else if (info.row != spy_loc.row)
		{
		spy_dir = return_to_hive(info, spy_loc);
		temp = spy_dir;
		spy_dir = is_cell_wax(info, spy_dir);
		if (spy_dir >= 0)
		{
			return (command_t) {
				.action = MOVE,
				.direction = spy_dir
			};
		}
		/* Breaking the WALL */
		if (spy_dir < 0)
		{
			if (spy_dir == -11)
			{
				/* Move random direction */
				return (command_t) {
					.action = MOVE,
					.direction = rand() % 8
				};
			}
			if (spy_dir == -10)
				spy_dir = 0;
			else
				spy_dir = spy_dir * -1;
			return (command_t) {
				.action = GUARD,
				.direction = spy_dir
			};
		}
	}
	else
	{
		flower_dir = find_neighbour(info, FLOWER);
		if (flower_dir >= 0)
		{
			return (command_t) {
				.action = GUARD,
				.direction = flower_dir
			};
		}
		if (info.player == 0)
		{
			enemy_dir = find_neighbour(info, BEE_1_WITH_FLOWER);
			if (enemy_dir >= 0)
			{
				return (command_t) {
					.action = GUARD,
					.direction = enemy_dir
				};
			}
		}
		else
		{
			enemy_dir = find_neighbour(info, BEE_0_WITH_FLOWER);
			if (enemy_dir >= 0)
			{
				return (command_t) {
					.action = GUARD,
					.direction = enemy_dir
				};
			}
		}
	}
	return (build_direction(info));
/*	return (command_t) {
		.action = BUILD,
		.direction = rand() % 8
	}; */
}
