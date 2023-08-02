/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:04:47 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 23:17:58 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../map/map_struct.h"
#include "../actor_logic/actor.h"
#include "../../libft/libft.h"

static inline void	free_tile_list(t_list **entity_list, t_map *map, void *mlx)
{
	t_list	*node;
	t_list	*next;

	node = *entity_list;
	while (node)
	{
		next = node->next;
		actor_free(node->content, map, mlx);
		node = next;
	}
	*entity_list = NULL;
}

void	free_tiles(t_map *map)
{
	int		i;
	int		j;
	t_tile	**matrix;

	matrix = map->tiles;
	i = 0;
	while ((matrix)[i])
	{
		j = 0;
		while (j < (int) map->width)
		{
			free_tile_list(&((matrix)[i][j]).entity_list, map, map->data->mlx);
			j++;
		}
		free((matrix)[i]);
		i++;
	}
	free(matrix);
	map->tiles = NULL;
}
