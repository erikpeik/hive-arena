#include "agent_pippuri.h"

int	open_map(int arr[NUM_ROWS][NUM_COLS], agent_info_t info, int type)
{
	int			min = VIEW_DISTANCE + 1;
	int			max = 0;
	int 		temp = 0;
	coords_t	target;
	int			dir;

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
		if(target.row != -1 && target.col != -1)
		{
			dir = return_to_hive(info, target);
			return (dir);
		}
		min++;
	}
	return (-1);
}
