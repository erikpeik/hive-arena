/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 13:40:14 by emende            #+#    #+#             */
/*   Updated: 2021/12/05 16:28:35 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_splits(char const *s, char c)
{
	size_t	i;
	size_t	res;
	size_t	new;

	res = 0;
	i = 0;
	new = 1;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && new == 1)
		{
			res++;
			new = 0;
		}
		else if (s[i] == c && new == 0)
			new = 1;
		i++;
	}
	return (res);
}

static char	**ft_malloc_split(char const *s, char c, char **array)
{
	size_t	i;
	size_t	word;

	i = 0;
	word = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			array[word] = (char *) malloc(sizeof(char) * \
					(ft_strclen(&s[i], c) + 1));
			if (!(array[word]))
				return (NULL);
			word++;
			i += ft_strclen(&s[i], c) + 1;
		}
		else
			i++;
	}
	array[word] = (char *) '\0';
	return (array);
}

static char	**ft_fill_array(char const *s, char c, char **array)
{
	size_t	i;
	size_t	word;
	size_t	count;

	i = 0;
	word = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			count = 0;
			while (s[i] != c && s[i])
			{
				array[word][count] = s[i];
				count++;
				i++;
			}
			array[word][count] = '\0';
			word++;
		}
		i++;
	}
	return (array);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **) malloc(sizeof(char *) * (ft_splits(s, c) + 1));
	if (!array)
		return (NULL);
	array = ft_malloc_split(s, c, array);
	if (!array)
	{
		while (*array)
		{
			free(*array);
			array++;
		}
		free(array);
		array = NULL;
		return (array);
	}
	array = ft_fill_array(s, c, array);
	return (array);
}
