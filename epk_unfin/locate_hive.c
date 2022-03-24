#include "agent_pippuri.h"

void locate_hive(int player, coords_t *hive_loc)
{
	if (player == 0)
		hive_loc->col = 3;
	else
		hive_loc->col = NUM_COLS - 4;
	if (row_spot == 11)
		hive_loc->row = row_spot - 1;
	else
		hive_loc->row = row_spot + 1;
}
