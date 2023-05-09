/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:44:48 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/09 18:19:07 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_LOAD_H
# define MAP_LOAD_H

# include "../../so_long.h"
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

// int		check_tile(t_map *map, char tile, t_point point);
// t_map	*map_init(t_list *row_list);
// t_map	*map_fill(t_map *map, t_list *row_list);
// t_list	*map_read(char *filepath);
t_map	*map_load(char *filepath);
t_map	*map_free(t_map **map);
void	enemy_free(void *enemy);

#endif
