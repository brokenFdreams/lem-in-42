/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_create_ant_queue.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 01:33:51 by dtimeon           #+#    #+#             */
/*   Updated: 2019/09/25 18:38:17 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "structs.h"


static t_ant	*init_ant(int ant_num)
{
	t_ant		*new;

	new = (t_ant *)malloc(sizeof(t_ant));
	if (!new)
		return (NULL);
	new->num = ant_num;
	new->current_vertex = NULL;
	return (new);
}

static int		add_ant(t_ant_queue **head_node, t_ant *ant)
{
	t_ant_queue		*new_node;

	new_node = (t_ant_queue *)malloc(sizeof(t_ant_queue));
	if (!new_node)
		return (0);
	new_node->ant = ant;
	if (*head_node)
		new_node->next = *head_node;
	else
		new_node->next = NULL;
	*head_node = new_node;
	return (1);
}

t_ant_queue			*create_ant_queue(int ants_left)
{
	t_ant_queue		*node;
	t_ant		*ant;

	node = NULL;
	while (ants_left > 0)
	{
		if (!(ant = init_ant(ants_left)) || !add_ant(&node, ant))
			ft_error("Memory allocation error");
		ants_left--;
	}
	return (node);
}
