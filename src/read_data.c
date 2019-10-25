/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:21:33 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/24 13:58:09 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					read_num(char *str)
{
	long long int	num;
	int				len;

	num = ft_strtol(str, NULL, 10);
	if (num < 1 || num == LLONG_MAX || num > INT_MAX)
		exit_with_map_format("Error: ants line is incorrect");
	while (*str)
	{
		if (!ft_isdigit(*str))
			exit_with_map_format("Error: ants line is incorrect");
		str++;
	}
	if ((len = ft_strlen(str)) > 11)
		exit_with_map_format("Error: too many ants");
	else if (len == 11 && num > INT_MAX)
		exit_with_map_format("Error: too many ants");
	return ((int)num);
}

t_list				*new_list_with_line(char *line)
{
	t_list			*new;

	new = ft_lstnew(NULL, 0);
	if (!new)
		ft_error("Memory allocation error\n");
	new->content = line;
	new->content_size = sizeof(char *);
	return (new);
}

int					is_blank(char *line)
{
	while (line && *line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

void				free_line_if_empty(char **line)
{
	if (*line && **line == '\0')
		free(*line);
}

/*
** Reading data from stdin
** if there's error, then call ft_error
*/

void				read_data(t_map_data *map_data)
{
	int				gnl;
	char			*line;
	t_list			*tmp;

	if ((gnl = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		if (line && *line)
			map_data->data = new_list_with_line(line);
		else
			exit_with_map_format("Error: empty lines found");
	}
	tmp = map_data->data;
	while ((gnl = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		if (line && !is_blank(line))
		{
			tmp->next = new_list_with_line(line);
			tmp = tmp->next;
		}
		else if (line)
			exit_with_map_format("Error: blank line found in map");
	}
	if (gnl == -1)
		exit_with_usage();
	free(line);
}
