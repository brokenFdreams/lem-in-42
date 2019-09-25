/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_queue_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:16:39 by dtimeon           #+#    #+#             */
/*   Updated: 2019/09/25 18:55:33 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			push(t_queue **queue, t_vertex *vertex)
{
	t_queue		*new;
	t_queue		*temp;

	new = (t_queue *)malloc(sizeof(t_queue));
	if (!new)
		ft_error("Memory allocation error");
	new->vertex = vertex;
	new->next = NULL;
	if (*queue)
	{
		temp = *queue;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*queue = new;	
}

t_vertex		*pop(t_queue **queue)
{
	t_vertex	*vertex;
	t_queue		*temp;

	if (!(*queue))
		return (NULL);
	vertex = (*queue)->vertex;
	temp = *queue;
	*queue =(*queue)->next;
	ft_memdel((void **)&temp);
	return(vertex);
}