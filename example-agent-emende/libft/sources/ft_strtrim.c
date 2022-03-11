/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 00:16:15 by emende            #+#    #+#             */
/*   Updated: 2021/12/13 17:11:16 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_start(char const *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	return (i);
}

static int	ft_get_end(char const *s)
{
	int	i;

	i = (int ) ft_strlen(s) - 1;
	if (i > 0)
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s)
{
	char	*trim;
	int		i;
	int		start;
	int		end;

	if (!s)
		return (NULL);
	start = ft_get_start(s);
	end = ft_get_end(s);
	if (start > end)
		return (ft_strdup(""));
	trim = (char *)malloc(sizeof(char) * (size_t)(end - start + 2));
	if (!trim)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		trim[i] = s[start];
		i++;
		start++;
	}
	trim[i] = '\0';
	return (trim);
}
