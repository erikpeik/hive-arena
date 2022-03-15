#include "agent_pippuri.h"

void locate_hive(int player, coords_t *hive_loc)
{
	if (player == 0)
	{
		hive_loc->row = (NUM_ROWS / 2);
		hive_loc->col = 1;
	}
	else
	{
		hive_loc->row = (NUM_ROWS / 2);
		hive_loc->col = (NUM_COLS - 2);
	}
}
