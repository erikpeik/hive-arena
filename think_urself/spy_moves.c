#include "agent_pippuri.h"

command_t	spy_moves(agent_info_t info)
{
	coords_t	move_here;
	int dir;

	if (info.bee == 1)
		move_here.row = 9;
	if (info.bee == 3)
		move_here.row = 15;
	if (info.player == 0)
		move_here.col= NUM_COLS / 2;
	else
		move_here.col = NUM_COLS / 2;
	if (toggle_bee1 == 1 && info.bee == 1)
	{
		if (info.col == move_here.col)
			toggle_bee1 = 0;
		else
		{
			dir = return_to_hive(info, move_here);
			if (dir >= 0)
				dir = is_cell_wax(info, dir);
			if (dir >= 0)
			{
				return (command_t) {
					.action = MOVE,
					.direction = dir
				};
			}
			if (dir < 0 && dir > -11)
			{
				if (dir == -10)
					dir = 0;
				else
					dir = dir * -1;
				return (command_t) {
					.action = GUARD,
					.direction = dir
				};
			}
		}
	}
	if (toggle_bee3 == 1 && info.bee == 3)
	{
		if (info.col == move_here.col)
			toggle_bee3 = 0;
		else
		{
			dir = return_to_hive(info, move_here);
			if (dir >= 0)
				dir = is_cell_wax(info, dir);
			if (dir >= 0)
			{
				return (command_t) {
					.action = MOVE,
					.direction = dir
				};
			}
			if (dir < 0 && dir > -11)
			{
				if (dir == -10)
					dir = 0;
				else
					dir = dir * -1;
				return (command_t) {
					.action = GUARD,
					.direction = dir
				};
			}
		}
	}
	return (command_t) {
		.action = MOVE,
		.direction = rand() % 8
	};
}
