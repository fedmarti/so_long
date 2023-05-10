/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 00:11:44 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/10 00:12:45 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_STRUCT_H
# define MAP_STRUCT_H
# include "../t_point/point.h"
# include "../../libft/libft.h"

typedef struct s_map{
	unsigned int	height;
	unsigned int	width;
	t_point			player_position;
	t_point			exit_position;
	t_list			*collectable_list;
	t_list			*enemy_list;
	t_list			*object_list;
	t_list			*entity_list;
	char			**map;
	char			*map_path;
}	t_map;

#endif