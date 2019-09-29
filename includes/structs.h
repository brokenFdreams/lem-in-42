/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:25:44 by dtimeon           #+#    #+#             */
/*   Updated: 2019/09/29 21:23:39 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _STRUCTS_H_
# define _STRUCTS_H_

# include "libft.h"

typedef struct			s_vertex
{
	char				*name;
	int					dist;
	char				is_occupied;
	t_list				*links;
	int					ants_num;
	char				is_start;
	char				is_end;
	char				is_visited;
	char				is_sorted;
	int					links_num;
	int					x;
	int					y;
	int					capacity;
}						t_vertex;

typedef struct			s_ant
{
	int					num;
	t_vertex			*current_vertex;
}						t_ant;


typedef struct			s_ant_queue
{
	t_ant				*ant;
	struct s_ant_queue	*next;
}						t_ant_queue;

typedef	struct			s_path
{
	t_vertex			*starting_vertex;
	int					steps;
	struct s_path		*next;
}						t_path;

typedef struct			s_path_combo
{
	t_vertex			*starting;
	int					lines_num;
	int					paths_num;
	int					steps;
	t_path				*paths;
	char				*name;
}						t_path_combo;

typedef struct			s_farm
{
	int					ants_num;
	t_vertex			*start;
	t_vertex			*end;
	t_vertex			**vertexes; //
	t_ant_queue			*ant_queue;
	t_ant				*first_in_queue;
	t_path_combo		*combo;
}						t_farm;

typedef struct			s_queue
{
	t_vertex			*vertex;
	struct s_queue		*next;
}						t_queue;
# endif