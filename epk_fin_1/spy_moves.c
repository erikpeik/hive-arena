#include "agent_pippuri.h"

command_t	spy_moves(agent_info_t info)
{
	coords_t	move_here;
	int dir;

	if (info.bee == 1)
		move_here.row = 3;
	if (info.bee == 3)
		move_here.row = 21;
	if (info.player == 0)
		move_here.col= (NUM_COLS / 2) + 2;
	else
		move_here.col = (NUM_COLS / 2) - 2;
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
		}
	}
	return (command_t) {
		.action = MOVE,
		.direction = rand() % 8
	};
}
