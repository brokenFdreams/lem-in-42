/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:25:44 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/08 18:51:08 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _STRUCTS_H_
# define _STRUCTS_H_

# include "libft.h"

typedef struct			s_vertex
{
	char				*name;
	int					dist;
	int					real_dist;
	char				is_occupied;
	t_list				*links;
	int					ants_num;
	char				is_start;
	char				is_end;
	char				is_visited;
	char				is_sorted;
	char				*path_name;
	int					path_num;
	int					links_num;
	int					x;
	int					y;
	int					capacity;
	struct s_vertex		*next;
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
	int					num;
	struct s_path		*next;
}						t_path;

typedef struct			s_path_combo
{
	t_vertex			*starting;
	// int					capacity;
	// float				average_path_len;
	int					num_of_paths_to_use;
	int					lines_num;
	int					paths_num;
	t_path				*paths;
	char				*name;
	int					is_best_one;
}						t_path_combo;

typedef struct			s_farm
{
	int					ants_num;
	t_vertex			*start;
	t_vertex			*end;
	t_vertex			**vertexes;
	int					vertex_num;
	t_ant_queue			*ant_queue;
	t_ant				*first_in_queue;
	t_path_combo		*combo;
}						t_farm;

typedef struct			s_queue
{
	t_vertex			*vertex;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_options
{
	int					path;
	int					color;
	int					stat;
	int					help;
	int					log;
}						t_options;

# endif
