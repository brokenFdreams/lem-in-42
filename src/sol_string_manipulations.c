/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_string_manipulations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:37:53 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 16:52:22 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		*convert_with_nessesery_zero(unsigned char num)
{
	char	*temp;
	char	*result;

	temp = ft_itoa(num);
	if (num < 10)
	{
		result = ft_strnew(3);
		if (!result)
			ft_error("Memory allocation error\n");
		result[0] = '0';
		result[1] = *temp;
		ft_strdel(&temp);
	}
	else
		result = temp;
	return (result);
}

void		ft_str_free_array(char ***array)
{
	char	**a;

	a = *array;
	while (*a)
		ft_strdel(a++);
	free(*array);
	*array = NULL;
}

char		*ft_join_str_array(char **array)
{
	size_t	len;
	char	*result;
	int		i;

	len = 0;
	i = 0;
	while (array[i])
		len += ft_strlen(array[i++]);
	if (!(result = ft_strnew(len)))
		ft_error("Memory allocation error\n");
	i = 0;
	while (*array)
	{
		ft_strcpy(result + i, *array);
		i += ft_strlen(*array);
		array++;
	}
	return (result);
}

char		*ft_join_strings(int str_num, ...)
{
	va_list	ap;
	char	*result;
	char	**args;
	int		i;

	va_start(ap, str_num);
	args = (char **)malloc(sizeof(char *) * (str_num + 1));
	if (!args)
		ft_error("Memory allocation error\n");
	args[str_num] = NULL;
	i = 0;
	while (i < str_num)
		if (!(args[i++] = ft_strdup(va_arg(ap, char *))))
			ft_error("Memory allocation error\n");
	va_end(ap);
	result = ft_join_str_array(args);
	ft_str_free_array(&args);
	return (result);
}

char		*create_time_string(struct tm *timeinfo)
{
	t_time	time_strings;
	char	*time_str;

	time_strings.month = convert_with_nessesery_zero(timeinfo->tm_mon + 1);
	time_strings.day = convert_with_nessesery_zero(timeinfo->tm_mday);
	time_strings.hour = convert_with_nessesery_zero(timeinfo->tm_hour);
	time_strings.minute = convert_with_nessesery_zero(timeinfo->tm_min);
	time_strings.second = convert_with_nessesery_zero(timeinfo->tm_sec);
	time_str = ft_join_strings(9, time_strings.day, "_", time_strings.month,
	"_", time_strings.hour, "_", time_strings.minute, "_", time_strings.second);
	ft_strdel(&time_strings.month);
	ft_strdel(&time_strings.day);
	ft_strdel(&time_strings.hour);
	ft_strdel(&time_strings.minute);
	ft_strdel(&time_strings.second);
	return (time_str);
}
