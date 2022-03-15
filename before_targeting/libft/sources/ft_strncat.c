/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:24:10 by emende            #+#    #+#             */
/*   Updated: 2021/12/10 17:42:50 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	z;

	z = 0;
	i = ft_strlen(s1);
	while ((z < n) && s2[z])
	{
		s1[i] = s2[z];
		z++;
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
