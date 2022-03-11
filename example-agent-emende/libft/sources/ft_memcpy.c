/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:19:05 by emende            #+#    #+#             */
/*   Updated: 2021/12/22 19:41:59 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ptr;

	if (!dst && !src)
		return (dst);
	ptr = dst;
	while (n >= sizeof(long))
	{
		*(unsigned long *) ptr = *(const unsigned long *) src;
		ptr += sizeof(long);
		src += sizeof(long);
		n -= sizeof(long);
	}
	if (n >= sizeof(int))
	{
		*(unsigned int *) ptr = *(const unsigned int *) src;
		ptr += sizeof(int);
		src += sizeof(int);
		n -= sizeof(int);
	}
	while (n-- > 0)
		*(unsigned char *) ptr++ = *(const unsigned char *) src++;
	return (dst);
}
