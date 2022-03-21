#include "agent_pippuri.h"

command_t	move_left_right(agent_info_t info, int *toggle)
{
	int dir, temp;
	coords_t loc;

	if (info.bee == 1)
	{
		if (info.player == 0)
			loc.col = 3;
		else
			loc.col = 26;
		loc.row = 3;
	}
	if (info.bee == 3)
	{
		if (info.player == 0)
			loc.col = 3;
		else
			loc.col = 26;
		loc.row = 26;
	}
	if (info.row == loc.row)
	{
		*toggle = 0;
		return (command_t) {
			.action = MOVE,
			.direction = rand() % 8
		};
	}
	if (info.col != loc.col)
	{
		dir = return_to_hive(info, loc);
		temp = dir;
		dir = is_cell_wax(info, dir);
		if (dir >= 0)
		{
			return (command_t) {
				.action = MOVE,
				.direction = dir
			};
		}
		/* Breaking the WALL */
		if (dir < 0)
		{
			if (dir == -11)
			{
				/* Move random direction */
				return (command_t) {
					.action = MOVE,
					.direction = rand() % 8
				};
			}
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
	else if (info.row != loc.row)
		{
		dir = return_to_hive(info, loc);
		temp = dir;
		dir = is_cell_wax(info, dir);
		if (dir >= 0)
		{
			return (command_t) {
				.action = MOVE,
				.direction = dir
			};
		}
		/* Breaking the WALL */
		if (dir < 0)
		{
			if (dir == -11)
			{
				/* Move random direction */
				return (command_t) {
					.action = MOVE,
					.direction = rand() % 8
				};
			}
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
