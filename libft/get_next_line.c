/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:19:26 by fsinged           #+#    #+#             */
/*   Updated: 2019/04/22 13:29:38 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_line(const int fd, char **str)
{
	char	*tmp;
	char	buf[BUFF_SIZE + 1];
	int		ret;

	while (!(ft_strchr(*str, '\n')) && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = *str;
		*str = ft_strjoin(*str, buf);
		ft_strdel(&tmp);
	}
	return (ret);
}

int	get_next_line(const int fd, char **line)
{
	static char	*str[2147483647];
	char		*tmp;

	if (fd < 0 || !line || BUFF_SIZE < 0 ||
		(!str[fd] && !(str[fd] = ft_strnew(1))) ||
		read_line(fd, &str[fd]) == -1)
		return (-1);
	if (ft_strchr(str[fd], '\n'))
	{
		tmp = str[fd];
		*line = ft_strsub(str[fd], 0, ft_strchr(str[fd], '\n') - str[fd]);
		str[fd] = ft_strsub(ft_strchr(str[fd], '\n'), 1,
							ft_strlen(ft_strchr(str[fd], '\n')) - 1);
		ft_strdel(&tmp);
	}
	else
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
	if (str[fd] || ft_strlen(*line))
		return (1);
	return (0);
}
