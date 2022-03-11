#include "agent_pippuri.h"

int fd;

command_t think(agent_info_t info)
{
	static int	arr[NUM_ROWS][NUM_COLS];
	int	flower_dir;
	coords_t hive_loc;

	if (info.turn == 0 || info.turn == 1)
	{
		fd = open("map_log", O_RDWR);
		if (fd < 0)
			panic("Open failed");
		initialize_map(arr);
	}
	cell_t bee = info.cells[VIEW_DISTANCE][VIEW_DISTANCE];
	update_map(arr, info);
//	ft_putstr_fd((const char *)arr[info.row], fd);
	print_map(arr, fd, info);
	if (info.player == 0)
	{
		hive_loc.row = (NUM_ROWS / 2);
		hive_loc.col = 1;
	}
	else
	{
		hive_loc.row = (NUM_ROWS / 2);
		hive_loc.col = (NUM_COLS - 2);
	}
	if (is_bee_with_flower(bee))
	{
		int	hive_dir = find_neighbour(info, hive_cell(info.player));
		if (hive_dir >= 0)
		{
			return (command_t) {
				.action = FORAGE,
				.direction = hive_dir
			};
		}
		hive_dir = return_to_hive(info, hive_loc);
		return (command_t) {
			.action = MOVE,
			.direction = hive_dir
		};
	}
	else
	{
		flower_dir = find_neighbour(info, FLOWER);
		if (flower_dir >= 0)
		{
			return (command_t) {
				.action = FORAGE,
				.direction = flower_dir
			};
		}
		flower_dir = find_distant(info, FLOWER);
		if (flower_dir >= 0)
		{
			return (command_t) {
				.action = MOVE,
				.direction = flower_dir
			};
		}
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
