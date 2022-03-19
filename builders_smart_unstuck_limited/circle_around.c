#include "agent_pippuri.h"

coords_t	circle_around(int arr[NUM_ROWS][NUM_COLS], agent_info_t info, int type, int offset)
{
	int col_max = NUM_COLS, col_min = 0;

	if (info.player == 0)
		col_max = 27;
	else
		col_min = 3;
	if (info.row - offset >= 0)
	{
		for (int i = -offset; i < offset; i++)
		{
			if (info.col + i >= col_min && info.col + i < col_max && arr[info.row - offset][info.col + i] == type)
			{
				return (coords_t){
					.row = info.row - offset,
					.col = info.col + i
				};
			}
		}
	}
	if (info.col + offset < col_max)
	{
		for (int i = -offset; i < offset; i++)
		{
			if (info.row + i >= 0 && info.row + i < NUM_ROWS && arr[info.row + i][info.col + offset] == type)
			{
				return (coords_t){
					.row = info.row + i,
					.col = info.col + offset
				};
			}
		}
	}
	if (info.row + offset < NUM_ROWS)
	{
		for (int i = offset; i > -offset; i--)
		{
			if (info.col + i >= col_min && info.col + i < col_max && arr[info.row + offset][info.col + i] == type)
			{
				return (coords_t){
					.row = info.row + offset,
					.col = info.col + i
				};
			}
		}
	}
	if (info.col - offset >= col_min)
	{
		for (int i = offset; i > -offset; i--)
		{
			if (info.row + i >= 0 && info.row + i < col_max && arr[info.row + i][info.col - offset] == type)
			{
				return (coords_t){
					.row = info.row + i,
					.col = info.col - offset
				};
			}
		}
	}
	return (coords_t) {
		.row = -1,
		.col = -1
	};
}
