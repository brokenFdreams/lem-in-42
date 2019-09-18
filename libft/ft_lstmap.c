/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:08:40 by fsinged           #+#    #+#             */
/*   Updated: 2019/06/26 16:34:53 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;
	t_list *buf;

	if (f && lst)
	{
		buf = f(lst);
		tmp = buf;
		lst = lst->next;
		while (lst)
		{
			tmp->next = f(lst);
			lst = lst->next;
			tmp = tmp->next;
		}
		return (buf);
	}
	return (NULL);
}
