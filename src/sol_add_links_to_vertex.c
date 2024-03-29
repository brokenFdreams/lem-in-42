/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_add_links_to_vertex.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 01:30:56 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 17:36:27 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "structs.h"

static t_vertex	*find_room(char *name, t_vertex **vertexes)
{
	int			i;

	i = 0;
	while (vertexes[i])
	{
		if (ft_strequ(vertexes[i]->name, name))
			return (vertexes[i]);
		i++;
	}
	return (NULL);
}

static void		link_rooms(t_vertex *room1, t_vertex *room2)
{
	ft_lstadd(&room1->links, ft_lstnew(&room2, sizeof(t_vertex *)));
	ft_lstadd(&room2->links, ft_lstnew(&room1, sizeof(t_vertex *)));
}

void			add_links(t_vertex **vertexes, t_map_data *map_data)
{
	int			i;
	char		**link;
	t_vertex	*room1;
	t_vertex	*room2;

	i = 0;
	while (map_data->ways[i])
	{
		link = ft_strsplit(map_data->ways[i], '-');
		if (!link || !link[0] || !link[1] || !*link[0] || !*link[1])
			ft_error("Error: incorrect link between vertexes\n");
		room1 = find_room(link[0], vertexes);
		room2 = find_room(link[1], vertexes);
		if (!room1 || !room2)
			ft_error("Error: link with non-initialized room found\n");
		link_rooms(room1, room2);
		ft_free_strings_array(&link);
		i++;
	}
}
