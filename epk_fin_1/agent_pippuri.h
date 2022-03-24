#ifndef AGENT_PIPPURI_H
#define AGENT_PIPPURI_H

# include <time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "agent.h"
# include <string.h>
# include "libft/libft.h"

void		print_map(int arr[NUM_ROWS][NUM_COLS], int fd, agent_info_t info, coords_t targets[5]);
void		update_map(int arr[NUM_ROWS][NUM_COLS], agent_info_t info);
void		initialize_map(int arr[NUM_ROWS][NUM_COLS]);
void		locate_hive(int player, coords_t *hive_loc);
int			return_to_hive(agent_info_t info, coords_t hive_loc);
int			find_distant(agent_info_t info, cell_t type, coords_t targets[5]);
int			find_neighbour(agent_info_t info, cell_t type);
int			open_map(int arr[NUM_ROWS][NUM_COLS], agent_info_t info, int type, coords_t targets[5]);
int			is_cell_free(agent_info_t info, int dir);
int			is_cell_wax(agent_info_t info, int dir);
int			is_cell_wax_city(agent_info_t info, int dir);
coords_t	circle_around(int arr[NUM_ROWS][NUM_COLS], agent_info_t info, int type, int offset);
command_t	builder_bees(agent_info_t info,  coords_t hive_loc);
command_t	build_direction(agent_info_t info);
command_t	spy_moves(agent_info_t info);

int	toggle_bee1;
int	toggle_bee3;

#endif
