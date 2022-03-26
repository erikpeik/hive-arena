#include "agent_pippuri.h"

command_t	move_up_down(agent_info_t info)
{
	coords_t move;
	int	dir;

	if (info.bee == 0)
		move.row = 4;
	else
		move.row = 20;
	if (info.player == 0)
		move.col = 3;
	else
		move.col = 26;
	if (toggle_bee0 == 1 && info.bee == 0)
	{
		if (info.row == move.row)
			toggle_bee0 = 0;
		else
		{
			dir = return_to_hive(info, move);
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
	if (toggle_bee4 == 1 && info.bee == 4)
	{
		if (info.row == move.row)
			toggle_bee4 = 0;
		else
		{
			dir = return_to_hive(info, move);
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
	if (toggle_bee0 == 0 && info.bee == 0)
	{
		return (command_t) {
			.action = MOVE,
			.direction = N
		};
	}
	if (toggle_bee4 == 0 && info.bee == 4)
	{
		return (command_t) {
			.action = MOVE,
			.direction = S
		};
	}
	return (command_t) {
		.action = MOVE,
		.direction = rand() % 8
	};
}
