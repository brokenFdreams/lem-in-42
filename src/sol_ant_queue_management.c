/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_ant_queue_management.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:33:42 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 16:31:10 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		del_ant_queue_till(t_ant_queue **head, t_ant_queue *to_keep)
{
	t_ant_queue	*temp;
	t_ant		*temp_ant;

	temp = *head;
	while (temp != to_keep)
	{
		*head = temp->next;
		temp_ant = temp->ant;
		ft_memdel((void **)&temp_ant);
		free(temp);
		temp = *head;
	}
}

static void		del_ant_queue_node(t_ant_queue **to_del, t_ant_queue *previous)
{
	previous->next = (*to_del)->next;
	ft_memdel((void **)&(*to_del)->ant);
	ft_memdel((void **)to_del);
}

void			renew_ant_queue(t_farm *farm)
{
	t_ant_queue	*ant_queue_head;
	t_ant_queue	*temp_ant_queue1;
	t_ant_queue	*temp_ant_queue2;

	ant_queue_head = farm->ant_queue;
	temp_ant_queue1 = ant_queue_head;
	while (temp_ant_queue1 && temp_ant_queue1->ant->current_vertex->is_end)
		temp_ant_queue1 = temp_ant_queue1->next;
	del_ant_queue_till(&ant_queue_head, temp_ant_queue1);
	while (temp_ant_queue1 && temp_ant_queue1->next)
	{
		temp_ant_queue2 = temp_ant_queue1->next;
		if (temp_ant_queue2->ant->current_vertex->is_end)
			del_ant_queue_node(&temp_ant_queue2, temp_ant_queue1);
		else
			temp_ant_queue1 = temp_ant_queue1->next;
	}
	farm->ant_queue = ant_queue_head;
}
