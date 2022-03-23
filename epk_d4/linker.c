#include "agent_pippuri.h"

command_t	linker(agent_info_t info, coords_t hive_loc)
{
	int	hive_dir, flower_dir;

	/* DROP flower in HIVE */
	if (is_bee_with_flower(bee) == 0)
	{
		flower_dir = find_neighbour(info, FLOWER);
		if (flower_dir >= 0)
		{
			return (command_t) {
				.action = FORAGE,
				.direction = flower_dir
			};
		}
	{
	hive_dir = find_neighbour(info, hive_cell(info.player));
	if (hive_dir >= 0)
	{
		return (command_t) {
			.action = FORAGE,
			.direction = hive_dir
		};
	}
}	
