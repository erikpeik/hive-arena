#include "agent_pippuri.h"

int	up_toggle = 1;
int	down_toggle = 1;

command_t	builder_bees(agent_info_t info,  coords_t hive_loc)
{
	int	spy_dir, temp, flower_dir, enemy_dir, dir;
	coords_t	spy_loc;
	coords_t	up_nurkka = {.row = 0, .col = NUM_COLS / 2};
	coords_t	down_nurkka = {.row = 24, .col = NUM_COLS / 2};

	if (up_toggle == 1 && info.bee == 0)
	{
		if (info.col == up_nurkka.col)
			up_toggle = 0;
		else
		{
			dir = return_to_hive(info, up_nurkka);
			dir = is_cell_free(info, dir);
			if (dir >= 0)
				{
				return (command_t) {
					.action = MOVE,
					.direction = dir
				};
			}
		}
	}
	if (down_toggle == 1 && info.bee == 4)
	{
		if (info.col == down_nurkka.col)
			down_toggle = 0;
		else
		{
			dir = return_to_hive(info, down_nurkka);
			dir = is_cell_free(info, dir);
			if (dir >= 0)
				{
				return (command_t) {
					.action = MOVE,
					.direction = dir
				};
			}
		}
	}
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
