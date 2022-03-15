/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                 :+:        +:+:+: :+:+:+    */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:23:14 by emende            #+#    #+#             */
/*   Updated: 2021/12/09 18:41:33 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	z;
	size_t	dstlen;
	size_t	srclen;

	if (dstsize == 0)
		return (ft_strlen(src));
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen > dstsize)
		return ((dstlen + srclen) - (dstlen - dstsize));
	i = ft_strlen(dst);
	z = 0;
	while (z < srclen && i < (dstsize - 1))
	{
		dst[i] = src[z];
		z++;
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (dstlen + srclen);
}
