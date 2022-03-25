#include "agent_pippuri.h"

void	update_map(int arr[NUM_ROWS][NUM_COLS], agent_info_t info)
{
	int col;
	int	row;

	if (info.row < VIEW_DISTANCE)
		row = -info.row;
	else
		row = -VIEW_DISTANCE;
	while (row <= VIEW_DISTANCE && info.row + row < NUM_ROWS)
	{
		if (info.col < VIEW_DISTANCE)
			col = -info.col;
		else
			col = -VIEW_DISTANCE;
		while (col <= VIEW_DISTANCE && info.col + col < NUM_COLS)
		{
			arr[info.row + row][info.col + col] = info.cells[VIEW_DISTANCE + row][VIEW_DISTANCE + col];
			//arr[info.row + row][info.col + col] = 0;
			col++;
		}
		row++;
	}
}

void initialize_map(int arr[NUM_ROWS][NUM_COLS])
{
	for (int row = 0; row < NUM_ROWS; row++)
	{
//		memset((void *) arr[row], -1, sizeof(int) * NUM_COLS);
		for (int col = 0; col < (NUM_COLS); col++)
			arr[row][col] = -1;
	}
}
