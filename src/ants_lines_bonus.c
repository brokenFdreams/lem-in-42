/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_lines_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:16:29 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 16:25:05 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	exit_with_ants(int lines_num)
{
	write(1, "All ants will be free in ", 25);
	ft_putnbr(lines_num);
	write(1, " lines.\n", 8);
}
