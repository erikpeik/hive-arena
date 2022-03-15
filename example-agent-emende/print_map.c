#include "agent_pippuri.h"



void	print_map(int arr[NUM_ROWS][NUM_COLS], int fd, agent_info_t info, coords_t targets[5])
{
	dprintf(fd, "Turn:	%d\n", info.turn);
	dprintf(fd, "B0: (%d, %d) - B1: (%d, %d) - B2: (%d, %d) - B3: (%d, %d) - B4: (%d, %d)\n", targets[0].row, targets[0].col, targets[1].row, targets[1].col, targets[2].row, targets[2].col, targets[3].row, targets[3].col, targets[4].row, targets[4].col);
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
