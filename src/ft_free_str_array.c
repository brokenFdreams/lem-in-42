/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 01:07:49 by dtimeon           #+#    #+#             */
/*   Updated: 2019/09/23 01:22:17 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		ft_free_strings_array(char ***array)
{
	char	**a;

	a = *array;
	while (*a)
		free(*a++);
	free(*array);
	*array = NULL;
}