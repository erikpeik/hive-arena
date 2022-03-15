/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:59:40 by emende            #+#    #+#             */
/*   Updated: 2021/12/27 20:27:50 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char	*str;
	size_t	s2_len;

	str = s1 + ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ft_memcpy(str, s2, s2_len);
	str += s2_len;
	*str = '\0';
	return (s1);
}
