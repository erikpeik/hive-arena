#include "agent_pippuri.h"

command_t	linker(agent_info_t info, coords_t hive_loc)
{
	int	hive_dir, flower_dir, col_spot, spy_dir, temp;
//	static int row_spot;
	coords_t	spot;

	if (info.turn == 4 || info.turn == 5)
	{
		if (rand() % 2 == 1)
			row_spot = 11;
		else
			row_spot = 13;
	}
//	row_spot = 13;
	if (info.player == 0)
		col_spot = 2;
	else
		col_spot = 27;
	spot.row = row_spot;
	spot.col = col_spot;
	if (info.col != spot.col)
	{
		spy_dir = return_to_hive(info, spot);
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
	else if (info.row != spot.row)
	{
		spy_dir = return_to_hive(info, spot);
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
		cell_t bee = info.cells[VIEW_DISTANCE][VIEW_DISTANCE];
		/* DROP flower in HIVE */
		if (is_bee_with_flower(bee) == 0)
		{
			flower_dir = find_neighbour(info, FLOWER);
			if (flower_dir >= 0)
			{
				return (command_t) {
					.action = FORAGE,
					.direction = flower_dir
				};
			}
		}
		hive_dir = find_neighbour(info, hive_cell(info.player));
		if (hive_dir >= 0)
		{
			return (command_t) {
				.action = FORAGE,
				.direction = hive_dir
			};
		}
	}
	return (command_t) {
		.action = FORAGE,
		.direction = rand() % 8
	};
}
