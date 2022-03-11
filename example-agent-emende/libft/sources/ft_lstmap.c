/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emende <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 22:44:44 by emende            #+#    #+#             */
/*   Updated: 2021/12/14 18:23:12 by emende           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_list(t_list **al)
{
	if (!(*al)->next)
		ft_free_list(&(*al)->next);
	free((*al)->content);
	free(*al);
	*al = NULL;
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*start;

	if (!lst || !f || !(*f))
		return (NULL);
	new = f(lst);
	if (!new)
		return (NULL);
	start = new;
	while (lst->next)
	{
		lst = lst->next;
		new->next = f(lst);
		if (!(new->next))
		{
			ft_free_list(&start);
			return (NULL);
		}
		new = new->next;
	}
	return (start);
}
