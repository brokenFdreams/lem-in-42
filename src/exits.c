/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:47:46 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 16:17:01 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Write error massage and exit program
*/

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(0);
}

void	exit_with_help(int color_flag)
{
	if (color_flag)
		switch_to_colour(2);
	write(1, "Lem-in\n", 7);
	if (color_flag)
		switch_to_colour(8);
	write(1, "A program to help ants find an exit from their farm\n", 52);
	if (color_flag)
		switch_to_default();
	write(1, "\nUsage: ./lem-in [options] < [path to map file]\n", 48);
	write(1, "\tList of options:\n\t\t-p --paths:", 31);
	write(1, "\tshow best found paths cobination\n", 34);
	write(1, "\t\t-c --color:\tuse colors\n", 25);
	write(1, "\t\t-s --stat:\tshow farm stat\n", 28);
	write(1, "\t\t-l --log:\tsave log file\n", 26);
	write(1, "\t\t-m --save_map:\tsave input map to file\n", 40);
	write(1, "\t\t-q --quiet:\tshow only lines number\n", 37);
	exit(0);
}

void	exit_with_map_format(char *message)
{
	write(1, message, ft_strlen(message));
	write(1, "\n\nUse the following map format:\n\n\t\
[Number of ants (int)]", 56);
	write(1, "\n\t[room x_axis(int) y_axis(int)] on separate line for each \
room", 63);
	write(1, "\n\t[room1-room2] on separate line for ways between rooms\n", 56);
	write(1, "\nNote that mandatiry commands [##start] and [##end] should \
preceed starting and ending rooms", 92);
	write(1, "\nComments: [#comment] and other commands: [##command] \
will also be accepted\n", 76);
	exit(0);
}

void	show_room_error(int code)
{
	if (code == -1)
		exit_with_map_format("Room name may not be blank");
	if (code == -1)
		exit_with_map_format("Room name may not contain \'-\' symbol");
	if (code == -2)
		exit_with_map_format("Two rooms may not have the same name");
	if (code == -3)
		exit_with_map_format("A room\'s name may not start with \'L\'");
}

void	exit_with_usage(void)
{
	write(1, "Usage: ./lem-in [options] < [path to map file] \
\nrun ./lem-in -h (or --help) for more information\n", 97);
	exit(0);
}
