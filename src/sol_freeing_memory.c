/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_freeing_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 01:00:48 by anna              #+#    #+#             */
/*   Updated: 2019/10/14 18:20:31 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				free_combo(t_path_combo **combo)
{
	ft_strdel(&(*combo)->name);
	clear_combo(combo, 1);
	ft_memdel((void **)combo);
}
