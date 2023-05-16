/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 00:11:44 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/16 18:30:20 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_STRUCT_H
# define MAP_STRUCT_H
# include "../t_point/point.h"
# include "../../libft/libft.h"

typedef struct s_tile{
	t_point	coordinates;
	t_list	*entity_list;
}	t_tile;

typedef struct s_map{
	unsigned int	height;
	unsigned int	width;
	t_tile			**tiles;
	struct s_actor	*player;
	struct s_actor	*exit;
	t_list			*collectable_list;
	t_list			*enemy_list;
	t_list			*object_list;
	t_list			*entity_list;
	char			**map;
	char			*map_path;
}	t_map;

#endif