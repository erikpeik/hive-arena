/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:11:10 by emende            #+#    #+#             */
/*   Updated: 2021/12/05 16:15:50 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_strclen -- find length of string until character found */

#include "libft.h"

size_t	ft_strclen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}
