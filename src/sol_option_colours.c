/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_option_colours.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:43:22 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/12 17:47:04 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				switch_to_colour(int colour_diff)
{
	colour_diff = (colour_diff > 12 ? colour_diff % 12 : colour_diff);
	if (colour_diff < 7)
	{
		ft_putstr("\033[1;");
		ft_putnbr(31 + colour_diff);
	}
	else
	{
		ft_putstr("\033[0;");
		ft_putnbr(31 + colour_diff - 7);
	}	
	write(1, "m", 2);	
}

void				switch_to_default(void)
{
	write(1, "\033[0m", 4);
}
