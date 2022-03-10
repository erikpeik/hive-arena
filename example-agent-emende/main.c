#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "agent.h"
#include <string.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char const *s, int fd)
{
	write(fd, s, strlen(s));
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd((char ) n + '0', fd);
}

static const coords_t se_offsets[] = {
	{-3, 0},
    {-3, 1},
	{-3, 2},
	{-3, 3},
	{-2, 3},
	{-1, 3},
	{0, 3},
	{1, 3},
	{2, 3},
	{3, 3},
	{3, 2},
	{3, 1},
	{3, 0},
	{3, -1},
	{3, -2},
	{3, -3},
	{2, -3},
	{1, -3},
	{0, -3},
	{-1, -3},
	{-2, -3},
	{-3, -3},
	{-3, -2},
	{-3, -1},
};

static const coords_t e_offsets[] = {
	{-2, 0}, // 0
	{-2, 1}, // 1
	{-2, 2}, // 2
	{-1, 2}, // 3
	{0, 2},
	{1, 2},
	{2, 2},
	{2, 1},
	{2, 0},
	{2, -1},
	{2, -2},
	{1, -2},
	{0, -2},
	{-1, -2},
	{-2, -2},
	{-2, -1}
};

coords_t direction_to_coords_3(coords_t from, int direction)
{
	coords_t offset = se_offsets[direction];

	return (coords_t) {
		.row = from.row + offset.row,
		.col = from.col + offset.col
	};
}

coords_t direction_to_coords_2(coords_t from, int direction)
{
	coords_t offset = e_offsets[direction];

	return (coords_t) {
		.row = from.row + offset.row,
		.col = from.col + offset.col
	};
}

int	find_distant(agent_info_t info, cell_t type)
{
	coords_t center = {VIEW_DISTANCE, VIEW_DISTANCE};

	for (int dir = 0 ; dir < 16 ; dir++)
	{
		coords_t coords = direction_to_coords_2(center, dir);
		cell_t distant = info.cells[coords.row][coords.col];
		if (distant == type)
			return (dir/2);
	}
    	for (int dir = 0 ; dir < 24 ; dir++)
	{
		coords_t coords = direction_to_coords_3(center, dir);
		cell_t distant = info.cells[coords.row][coords.col];
		if (distant == type)
			return (dir/3);
	}
	return (-1);
}

int find_neighbour(agent_info_t info, cell_t type)
{
	coords_t center = {VIEW_DISTANCE, VIEW_DISTANCE};

	for(int dir = 0 ; dir < 8 ; dir++)
	{
		coords_t coords = direction_to_coords(center, dir);
		cell_t neighbour = info.cells[coords.row][coords.col];
		if (neighbour == type)
		{
			return dir;
		}
	}
	return -1;
}

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

void	print_map(int arr[NUM_ROWS][NUM_COLS], int fd, agent_info_t info)
{
	dprintf(fd, "Turn:	%d\n", info.turn);
	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			if (arr[row][col] == -1)
				ft_putstr_fd("~", fd);
			else if (arr[row][col] == 0)
				ft_putstr_fd(".", fd);
			else if (arr[row][col] == 1 || arr[row][col] == 2)
				ft_putstr_fd("B" , fd);
			else if (arr[row][col] == 3 || arr[row][col] == 4)
				ft_putstr_fd("f", fd);
			else if (arr[row][col] == 5)
				ft_putstr_fd("F", fd);
			else if (arr[row][col] == 7 || arr[row][col] == 8)
				ft_putstr_fd("H", fd);
			else
				ft_putnbr_fd(arr[row][col], fd);
			ft_putchar_fd(' ', fd);
		}
		ft_putchar_fd('\n', fd);
	}
	ft_putchar_fd('\n', fd);
}

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
