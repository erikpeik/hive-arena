#include "agent_pippuri.h"

int fd;

command_t think(agent_info_t info)
{
	static int	arr[NUM_ROWS][NUM_COLS];
	int	flower_dir, cloud_dir, enemy_dir;
	coords_t hive_loc;

	/* Creating the map */
	if (info.turn == 0 || info.turn == 1)
	{
		fd = open("map_log", O_RDWR);
		if (fd < 0)
			panic("Open failed");
		initialize_map(arr);
	}

	/* Update map with area what current bee can see */
	cell_t bee = info.cells[VIEW_DISTANCE][VIEW_DISTANCE];
	update_map(arr, info);
	//ft_putstr_fd((const char *)arr[info.row], fd);
	print_map(arr, fd, info);

	/* Locate home Hive */
	locate_hive(info.player, &hive_loc);
	if (is_bee_with_flower(bee))
	{
		/* Return bee to Hive if it's next to */
		int	hive_dir = find_neighbour(info, hive_cell(info.player));
		if (hive_dir >= 0)
		{
			return (command_t) {
				.action = FORAGE,
				.direction = hive_dir
			};
		}
		/* Find's direction where is Hive */
		hive_dir = return_to_hive(info, hive_loc);
		hive_dir = is_cell_free(info, hive_dir);
		if (hive_dir >= 0)
			{
			return (command_t) {
				.action = MOVE,
				.direction = hive_dir
			};
		}
		/* Move random direction */
		return (command_t) {
			.action = MOVE,
			.direction = rand() % 8
		};
	}
	else
	{
		/* Pick flower if it's neightbour */
		flower_dir = find_neighbour(info, FLOWER);
		if (flower_dir >= 0)
		{
			return (command_t) {
				.action = FORAGE,
				.direction = flower_dir
			};
		}
		/* Looks flower in view distance */
		flower_dir = find_distant(info, FLOWER);
		if (flower_dir >= 0)
			flower_dir = is_cell_free(info, flower_dir);
		if (flower_dir >= 0)
		{
			return (command_t) {
				.action = MOVE,
				.direction = flower_dir
			};
		}
		/* Are there enemies with flowers nearby */
		if (info.player == 0)
		{
			enemy_dir = find_neighbour(info, BEE_1_WITH_FLOWER);
			if (enemy_dir >= 0)
			{
				return (command_t) {
					.action = GUARD,
					.direction = enemy_dir
				};
			}
		}
		else
		{
			enemy_dir = find_neighbour(info, BEE_0_WITH_FLOWER);
			if (enemy_dir >= 0)
			{
				return (command_t) {
					.action = GUARD,
					.direction = enemy_dir
				};
			}
		}
		/* Are there enemies with flowers that we can see */
		if (info.player == 0)
		{
			enemy_dir = find_distant(info, BEE_1_WITH_FLOWER);
			if (enemy_dir >= 0)
				enemy_dir = is_cell_free(info, enemy_dir);
			if (enemy_dir >= 0)
			{
				return (command_t) {
					.action = MOVE,
					.direction = enemy_dir
				};
			}
		}
		else
		{
			enemy_dir = find_distant(info, BEE_0_WITH_FLOWER);
			if (enemy_dir >= 0)
				enemy_dir = is_cell_free(info, enemy_dir);
			if (enemy_dir >= 0)
			{
				return (command_t) {
					.action = MOVE,
					.direction = enemy_dir
				};
			}
		}
		/* Looking flowers in map */
		flower_dir = open_map(arr, info, FLOWER);
		if (flower_dir >= 0)
			flower_dir = is_cell_free(info, flower_dir);
		if (flower_dir >= 0)
		{
			return (command_t) {
				.action = MOVE,
				.direction = flower_dir
			};
		}
		/* Looking not visited places in map */
		cloud_dir = open_map(arr, info, -1);
		if (cloud_dir >= 0)
			cloud_dir = is_cell_free(info, cloud_dir);
		if (cloud_dir >= 0)
		{
			return (command_t) {
				.action = MOVE,
				.direction = cloud_dir
			};
		}
		/* Look for enemies with flower(s) from MAP */
		if (info.player == 0)
		{
			enemy_dir = open_map(arr, info, BEE_1_WITH_FLOWER);
			if (enemy_dir >= 0)
				enemy_dir = is_cell_free(info, enemy_dir);
			if (enemy_dir >= 0)
			{
				return (command_t) {
					.action = MOVE,
					.direction = enemy_dir
				};
			}
		}
		else
		{
			enemy_dir = open_map(arr, info, BEE_0_WITH_FLOWER);
			if (enemy_dir >= 0)
				enemy_dir = is_cell_free(info, enemy_dir);
			if (enemy_dir >= 0)
			{
				return (command_t) {
					.action = MOVE,
					.direction = enemy_dir
				};
			}

		}
		/* Move random direction */
		return (command_t) {
			.action = MOVE,
			.direction = rand() % 8
		};
	}
}

int main(int argc, char **argv)
{
	if (argc < 3)
		panic("Usage: ./agent arena_host arena_ip");

	srand(time(NULL) + getpid());

	char *host = argv[1];
	int port = atoi(argv[2]);
	char *team_name = "Eerikin Pippuri Kebab";

	agent_main(host, port, team_name, think);
}
