/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende & altikka                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:53:13 by emende            #+#    #+#             */
/*   Updated: 2021/12/27 13:49:14 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memset_one(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		((unsigned char *) b)[i++] = (unsigned char ) c;
	return (b);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	arr[sizeof(long)];
	unsigned long	*ptr_l;
	unsigned int	*ptr_i;

	if (len < sizeof(long) + sizeof(int))
		return (ft_memset_one(b, c, len));
	ptr_l = b;
	ft_memset_one((void *) arr, c, sizeof(long));
	while (len >= sizeof(long))
	{
		*(long *) ptr_l++ = *(long *) arr;
		len -= sizeof(long);
	}
	ptr_i = (unsigned int *) ptr_l;
	if (len >= sizeof(int))
	{
		*(int *) ptr_i++ = *(int *) arr;
		len -= sizeof(int);
	}
	if (len > 0)
		ft_memset_one((void *) ptr_i, c, len);
	return (b);
}
