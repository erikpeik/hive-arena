#include "agent_pippuri.h"

 // int fd;

command_t think(agent_info_t info)
{
	static int	arr[NUM_ROWS][NUM_COLS];
	static coords_t	targets[5];
	int	hive_dir, flower_dir, cloud_dir, enemy_dir, esc_dir, temp, temp_action;
	coords_t hive_loc;
	command_t	catcher;


	/* Creating the map */
	if (info.turn == 0 || info.turn == 1)
	{
//		fd = open("map_log", O_RDWR);
//		if (fd < 0)
//			panic("Open failed");
		initialize_map(arr);
	}
	targets[info.bee].col = -1;
	targets[info.bee].row = -1;

	/* Update map with area what current bee can see */
	cell_t bee = info.cells[VIEW_DISTANCE][VIEW_DISTANCE];
	update_map(arr, info);
	//ft_putstr_fd((const char *)arr[info.row], fd);
//	print_map(arr, fd, info, targets);

	/* Locate home HIVE */
	locate_hive(info.player, &hive_loc);

	/* SPY LOCATION */
	if (info.bee == 0 || info.bee == 4)
	{
		catcher = builder_bees(info, hive_loc);
		return (catcher);
	}
	if (is_bee_with_flower(bee))
	{
		/* DROP flower in HIVE */
		hive_dir = find_neighbour(info, hive_cell(info.player));
		if (hive_dir >= 0)
		{
			return (command_t) {
				.action = FORAGE,
				.direction = hive_dir
			};
		}
		/* Find direction of the HIVE */
		hive_dir = return_to_hive(info, hive_loc);
		if((abs(hive_loc.row - info.row) <= 4) && (abs(hive_loc.col - info.col) <= 4)) //
		{
			hive_dir = is_cell_wax(info, hive_dir);
			if (hive_dir >= 0)
				{
				return (command_t) {
					.action = MOVE,
					.direction = hive_dir
				};
			}
			/* Breaking the WALL */
			if (hive_dir < 0)
			{
				if (hive_dir == -11)
				{
					/* Move random direction */
					return (command_t) {
						.action = MOVE,
						.direction = rand() % 8
					};
				}
				if (hive_dir == -10)
					hive_dir = 0;
				else
					hive_dir = hive_dir * -1;
				return (command_t) {
					.action = GUARD,
					.direction = hive_dir
				};
			}
		}
		else
		{
			temp = hive_dir;
			hive_dir = is_cell_free(info, hive_dir);
			if (hive_dir >= 0)
				{
				return (command_t) {
					.action = MOVE,
					.direction = hive_dir
				};
			}
			/* Breaking the WALL */
			if (hive_dir == -2)
				return (command_t) {
					.action = GUARD,
					.direction = temp
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
			if (info.player == 0)
			{
				if (info.col >= NUM_COLS/2 + 10)
					temp_action = GUARD;
				else
					temp_action = FORAGE;
			}
			else
			{
				if (info.col >= NUM_COLS/2 - 10)
					temp_action = FORAGE;
				else
					temp_action = GUARD;
			}
			return (command_t) {
				.action = temp_action,
				.direction = flower_dir
			};
		}
		/* ESCAPE FROM WAX CITY */
		if ((info.col == 0) || (info.col == 29))
		{
			if (abs(hive_loc.row - info.row) < 4) //<- 2 never works!
			{
				if (info.row < (NUM_ROWS / 2))
				{
					esc_dir = is_cell_wax_city(info, N);
					if (esc_dir == N)
					{
						return (command_t) {
							.action = GUARD,
							.direction = N
						};
					}
					else
					{
						esc_dir = is_cell_wax(info, N);
						if (esc_dir >= 0)
						{
							return (command_t) {
								.action = MOVE,
								.direction = esc_dir
							};
						}
						/* Breaking the WALL */
						if (esc_dir < 0)
						{
							if (esc_dir == -11)
							{
								/* Move random direction */
								return (command_t) {
									.action = MOVE,
									.direction = rand() % 8
								};
							}
							if (esc_dir == -10)
								esc_dir = 0;
							else
								esc_dir = esc_dir * -1;
							return (command_t) {
								.action = GUARD,
								.direction = esc_dir
							};
						}
					}
				}
				if (info.row >= (NUM_ROWS / 2))
				{
					esc_dir = is_cell_wax_city(info, S);
					if (esc_dir == S)
					{
						return (command_t) {
							.action = GUARD,
							.direction = S
						};
					}
					else
					{
						esc_dir = is_cell_wax(info, S);
						if (esc_dir >= 0)
						{
							return (command_t) {
								.action = MOVE,
								.direction = esc_dir
							};
						}
						/* Breaking the WALL */
						if (esc_dir < 0)
						{
							if (esc_dir == -11)
							{
								/* Move random direction */
								return (command_t) {
									.action = MOVE,
									.direction = rand() % 8
								};
							}
							if (esc_dir == -10)
								esc_dir = 0;
							else
								esc_dir = esc_dir * -1;
							return (command_t) {
								.action = GUARD,
								.direction = esc_dir
							};
						}
					}
				}
			}
		}
		/* Look for a flower in view distance */
		flower_dir = find_distant(info, FLOWER, targets);
		if (flower_dir >= 0)
		{
			temp = flower_dir;
			flower_dir = is_cell_free(info, flower_dir);
		}
		if (flower_dir >= 0)
		{
			return (command_t) {
				.action = MOVE,
				.direction = flower_dir
			};
		}
		/* Breaking the WALL */
		if (flower_dir == -2)
			return (command_t) {
				.action = GUARD,
				.direction = temp
		};
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
		/* Looking flowers in map */
		flower_dir = open_map(arr, info, FLOWER, targets);
		if (flower_dir >= 0)
		{
			temp = flower_dir;
			flower_dir = is_cell_free(info, flower_dir);
		}
		if (flower_dir >= 0)
		{
			return (command_t) {
				.action = MOVE,
				.direction = flower_dir
			};
		}
		/* Breaking the WALL */
		if (flower_dir == -2)
			return (command_t) {
				.action = GUARD,
				.direction = temp
		};
		/* Looking not visited places in map */
		cloud_dir = open_map(arr, info, -1, targets);
		if (cloud_dir >= 0)
		{
			temp = cloud_dir;
			cloud_dir = is_cell_free(info, cloud_dir);
		}
		if (cloud_dir >= 0)
		{
			return (command_t) {
				.action = MOVE,
				.direction = cloud_dir
			};
		}
		/* Breaking the WALL */
		if (cloud_dir == -2)
			return (command_t) {
				.action = GUARD,
				.direction = temp
		};
		/* Are there enemies with flowers that we can see */
		if (info.player == 0)
		{
			enemy_dir = find_distant(info, BEE_1_WITH_FLOWER, targets);
			if (enemy_dir >= 0)
			{
				temp = enemy_dir;
				enemy_dir = is_cell_free(info, enemy_dir);
			}
			if (enemy_dir >= 0)
			{
				return (command_t) {
					.action = MOVE,
					.direction = enemy_dir
				};
			}
			/* Breaking the WALL */
			if (enemy_dir == -2)
				return (command_t) {
					.action = GUARD,
					.direction = temp
			};
		}
		else
		{
			enemy_dir = find_distant(info, BEE_0_WITH_FLOWER, targets);
			if (enemy_dir >= 0)
			{
				temp = enemy_dir;
				enemy_dir = is_cell_free(info, enemy_dir);
			}
			if (enemy_dir >= 0)
			{
				return (command_t) {
					.action = MOVE,
					.direction = enemy_dir
				};
			}
			/* Breaking the WALL */
			if (enemy_dir == -2)
				return (command_t) {
					.action = GUARD,
					.direction = temp
			};
		}
		/* Look for enemies with flower(s) from MAP */
		if (info.player == 0)
		{
			enemy_dir = open_map(arr, info, BEE_1_WITH_FLOWER, targets);
			if (enemy_dir >= 0)
			{
				temp = enemy_dir;
				enemy_dir = is_cell_free(info, enemy_dir);
			}
			if (enemy_dir >= 0)
			{
				return (command_t) {
					.action = MOVE,
					.direction = enemy_dir
				};
			}
			/* Breaking the WALL */
			if (enemy_dir == -2)
				return (command_t) {
					.action = GUARD,
					.direction = temp
			};
		}
		else
		{
			enemy_dir = open_map(arr, info, BEE_0_WITH_FLOWER, targets);
			if (enemy_dir >= 0)
			{
				temp = enemy_dir;
				enemy_dir = is_cell_free(info, enemy_dir);
			}
			if (enemy_dir >= 0)
			{
				return (command_t) {
					.action = MOVE,
					.direction = enemy_dir
				};
			}
			/* Breaking the WALL */
			if (enemy_dir == -2)
				return (command_t) {
					.action = GUARD,
					.direction = temp
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
