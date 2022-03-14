/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 12:57:06 by emende            #+#    #+#             */
/*   Updated: 2022/01/12 01:20:47 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_line_append(char **line, char **arr)
{
	char	*new;

	new = ft_strjoin(*line, *arr);
	if (!new)
		return (-1);
	free(*line);
	*line = new;
	return (0);
}

static int	ft_malloc_buffer(char **arr)
{
	free(*arr);
	*arr = ft_strnew(BUFF_SIZE);
	if (*arr == NULL)
		return (-1);
	return (0);
}

static int	ft_final_touches(char **line, char **arr, char *eol)
{
	char	*new;

	*eol = '\0';
	ft_line_append(line, arr);
	if (*line == NULL)
		return (-1);
	new = ft_strdup(eol + 1);
	if (!new)
		return (-1);
	free(*arr);
	*arr = new;
	return (1);
}

static int	ft_read_to_buffer(char **line, char **arr, const int fd, char *eol)
{
	ssize_t	ret;

	while (!eol)
	{
		if (ft_line_append(line, arr) == -1)
			return (-1);
		if (ft_malloc_buffer(arr) == -1)
			return (-1);
		ret = read(fd, *arr, BUFF_SIZE);
		if (ret < 0)
			return (-1);
		if (ret == 0)
		{
			if (ft_strlen(*line) > 0)
				return (1);
			ft_strdel(arr);
			ft_strdel(line);
			return (0);
		}
		eol = ft_strchr(*arr, '\n');
	}
	return (ft_final_touches(line, arr, eol));
}

int	get_next_line(const int fd, char **line)
{
	static char	*arr[FD_SIZE];
	char		*eol;

	if (fd < 0 || fd > FD_SIZE || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!arr[fd])
		if (ft_malloc_buffer(&arr[fd]) == -1)
			return (-1);
	*line = ft_strnew(0);
	if (*line == NULL)
		return (-1);
	eol = ft_strchr(arr[fd], '\n');
	if (eol)
		return (ft_final_touches(line, &arr[fd], eol));
	return (ft_read_to_buffer(line, &arr[fd], fd, eol));
}
