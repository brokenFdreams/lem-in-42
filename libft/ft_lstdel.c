/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:22:50 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/21 15:30:50 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *tmp;
	t_list *buf;

	if (alst && *alst)
	{
		buf = *alst;
		while (buf)
		{
			tmp = buf->next;
			del(buf->content, buf->content_size);
			free(buf);
			buf = tmp;
		}
		*alst = NULL;
	}
}
