#include "agent_pippuri.h"

command_t	builder_bees(agent_info_t info,  coords_t hive_loc)
{
	int	spy_dir, temp, flower_dir, enemy_dir;
	coords_t	spy_loc;

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

	if ((info.bee == 0 && info.col != spy_loc.col) || (info.bee == 4 && info.col != spy_loc.col)) //spy
	{
		spy_dir = return_to_hive(info, spy_loc);
		temp = spy_dir;
		spy_dir = is_cell_free(info, spy_dir);
		if (spy_dir >= 0)
			{
			return (command_t) {
				.action = MOVE,
				.direction = spy_dir
			};
		}
		/* Breaking the WALL */
		if (spy_dir == -2)
			return (command_t) {
				.action = GUARD,
				.direction = temp
		};
		/* Move random direction */
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
	return (command_t) {
		.action = BUILD,
		.direction = rand() % 8
	};
}
