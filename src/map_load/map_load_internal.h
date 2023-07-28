/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:59:26 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/28 00:35:22 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_LOAD_INTERNAL_H
# define MAP_LOAD_INTERNAL_H

# include <stdbool.h>
# include "../map/map_struct.h"
# include "../../so_long.h"
# include "../../libft/libft.h"

int		check_tile(t_map *map, char tile, t_point point);
t_map	*map_init(t_list *row_list, char *filepath, t_data *data);
t_map	*map_fill(t_map *map, t_list *row_list);
t_list	*map_read(char *filepath);
bool	has_player_and_exit(t_map *map);
bool	is_rectangle(char **map, unsigned int width);
void	*enemy_init(t_point	position, char *filepath);
int		map_list_append(t_map *map, char tile, t_point position);
void	enemy_free(void *enemy, void *mlx);
bool	valid_map_check(t_map *map);
void	free_tiles(t_map *map);

#endif
