#include "agent_pippuri.h"

int	open_map(int arr[NUM_ROWS][NUM_COLS], agent_info_t info, int type, coords_t targets[5])
{
	int			min = VIEW_DISTANCE + 1;
	int			max = 0;
	int 		temp = 0;
	coords_t	target;
	int			dir;
	int 		i;
	int			is_targeted = 0;

	if (info.col < (NUM_COLS / 2))
	{
		temp = NUM_COLS - info.col;
		if (temp > max)
			max = temp;
	}
	else
	{
		temp = NUM_COLS;
		if (temp > max)
			max = temp;
	}
	if (info.row < (NUM_ROWS / 2))
	{
		temp = NUM_ROWS - info.row;
		if (temp > max)
			max = temp;
	}
	else
	{
		temp = NUM_ROWS;
		if (temp > max)
			max = temp;
	}
	while (min <= max)
	{
		target = circle_around(arr, info, type, min);
		if (target.row != -1 && target.col != -1)
		{
			if (type == FLOWER)
			{
				i = 0;
				while (i < 5)
				{	
					if (targets[i].row == target.row && targets[i].col == target.col)
					{
						is_targeted = 1;
						break ;
					}
					i++;
				}
				if (is_targeted == 0)
				{
					targets[info.bee].row = target.row;
					targets[info.bee].col = target.col;
				}
				else
				{
					is_targeted = 0;
					min++;
					continue ;
				}
			}
			dir = return_to_hive(info, target);
			return (dir);
		}
		min++;
	}
	return (-1);
}
