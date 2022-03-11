#ifndef AGENT_PIPPURI_H
#define AGENT_PIPPURI_H

# include <time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "agent.h"
# include <string.h>
# include "libft/includes/libft.h"

void	print_map(int arr[NUM_ROWS][NUM_COLS], int fd, agent_info_t info);
void	update_map(int arr[NUM_ROWS][NUM_COLS], agent_info_t info);
void	initialize_map(int arr[NUM_ROWS][NUM_COLS]);
int	return_to_hive(agent_info_t info, coords_t hive_loc);
int	find_distant(agent_info_t info, cell_t type);
int find_neighbour(agent_info_t info, cell_t type);

#endif
