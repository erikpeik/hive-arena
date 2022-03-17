#include "agent_pippuri.h"

int	return_to_hive(agent_info_t info, coords_t hive_loc)
{
	if (info.col > hive_loc.col)
	{
		if (info.row > hive_loc.row)
			return (NW);
		else if (info.row < hive_loc.row)
			return (SW);
		else
			return (W);
	}
	else if (info.col < hive_loc.col)
	{
		if (info.row > hive_loc.row)
			return (NE);
		else if (info.row < hive_loc.row)
			return (SE);
		else
			return (E);
	}
	else
	{
		if (info.row > hive_loc.row)
			return (N);
		else
			return (S);
	}
}
