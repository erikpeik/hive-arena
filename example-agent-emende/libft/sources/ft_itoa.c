/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <emende@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:34:48 by emende            #+#    #+#             */
/*   Updated: 2021/12/05 21:42:11 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill_itoa(char *itoa, int n, int len)
{
	while (n > 0)
	{
		itoa[len--] = n % 10 + '0';
		n = n / 10;
	}
	return (itoa);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		len;

	len = (int ) ft_intlen(n);
	itoa = (char *) malloc(sizeof(char) * ((size_t)len + 1));
	if (!(itoa))
		return (NULL);
	itoa[len--] = '\0';
	if (n == 0)
		itoa[0] = '0';
	if (n < 0)
	{
		if (n == -2147483648)
		{
			itoa[len--] = '8';
			n = n / 10;
		}
		n = -n;
		itoa[0] = '-';
	}
	itoa = ft_fill_itoa(itoa, n, len);
	return (itoa);
}
