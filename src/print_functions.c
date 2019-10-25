/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:26:33 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 15:57:02 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_map(int fd, t_list *map)
{
	while (map)
	{
		write(fd, (char *)map->content,
				ft_strlen((char *)map->content));
		write(fd, "\n", 1);
		map = map->next;
	}
	write(fd, "\n", 1);
}

void			print_number_of_lines(int lines_num)
{
	write(1, "All ants will be free in ", 25);
	ft_putnbr(lines_num);
	write(1, " lines.\n", 8);
}
