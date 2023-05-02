/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:25:49 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/02 23:54:57 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_load.h"
#include <stdbool.h>

int	check_tile(t_map *map, char tile, t_point point)
{
	if (tile == Player)
	{
		if (map->player_position.x || map->player_position.x)
			return (1);
		map->player_position = point;
	}
	else if (tile == Enemy || tile == Collectable)
		return (map_list_append(map, tile, point));
	else if (tile == Exit)
	{
		if (map->exit_position.x || map->exit_position.y)
			return (1);
		map->exit_position = point;
	}
	return (0);
}

bool	flood_fill(char **map, t_point	position)
{
	char	tile;
	int		i;

	while (i < 4)
	{
		//get_next_direction();
		//vector math...
	}
}

static char	**map_dup(char **map, unsigned int height)
{
	char	**temp_map;
	int		i;

	i = 0;
	temp_map = malloc(sizeof(char *) * (height + 1));
	if (!temp_map)
		return (NULL);
	while (i < height)
	{
		temp_map[i] = ft_strdup(map[i]);
		if (!temp_map)
			return (ft_free_matrix(&temp_map, i));
		i++;
	}
	temp_map[i] = NULL;
	return (temp_map);
}

bool	valid_map_check(t_map *map)
{
	char	**temp_map;
	int		i;

	temp_map = map_dup(map->map, map->height);
	if (!temp_map)
		return (false);
	
	
	
}