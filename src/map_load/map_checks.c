/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:25:49 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/15 18:26:52 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_load_internal.h"
#include "../../so_long.h" //also gotta remove

//for the type of objects that need to be unique (player, exit...)
//returns 1 if they have already been found
//returns 0 and adds their address to the map struct if not
int	check_uniqueness(t_map *map, char tile, t_point point)
{
	t_actor	**actor;

	if (tile == Player)
		actor = &map->player;
	else
		actor = &map->exit;
	if (*actor)
		return (1);
	*actor = map->tiles[point.x][point.y].entity_list->content;
	return (0);
}

int	check_tile(t_map *map, char tile, t_point point)
{
	map->tiles[point.x][point.y].coordinates = point;
	if (tile != Empty && tile != Void)
	{
		if (map_list_append(map, tile, point))
			return (1);
	}
	if (tile == Player || tile == Exit)
	{
		if (check_uniqueness(map, tile, point))
			return (1);
	}
	return (0);
}

static bool	flood_fill(char **map, t_point	position)
{
	char	tile;
	int		i;
	t_point	directions[4];
	t_point	neighbor;

	ft_get_directions(directions);
	map[position.y][position.x] = Wall;
	i = -1;
	while (++i < 4)
	{
		neighbor = point_add(position, directions[i]);
		if (neighbor.x < 0 || neighbor.y < 0)
			continue ;
		tile = map[neighbor.y][neighbor.x];
		if (tile != Void && tile != Wall)
		{
			if (!flood_fill(map, neighbor))
				return (false);
		}
		if (tile == Void)
			return (false);
	}
	return (true);
}

static char	**map_dup(char **map, unsigned int height)
{
	char	**temp_map;
	int		i;

	i = 0;
	if (!map)
		return (NULL);
	temp_map = malloc(sizeof(char *) * (height + 1));
	if (!temp_map)
		return (NULL);
	while (i < (int)height)
	{
		temp_map[i] = ft_strdup(map[i]);
		if (!temp_map)
			return (ft_free_matrix((void ***)&temp_map, i));
		i++;
	}
	temp_map[i] = NULL;
	return (temp_map);
}

//checks if there are any remaining non wall tiles after flood fill
static bool	check_out_of_reach(char **map)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i] != 0)
		{
			if (map[j][i] != Wall && map[j][i] != Empty)
				return (false);
			i++;
		}
		j++;
	}
	return (true);
}

//runs all the check to confirm the validity of the map file
//the map needs to be a rectangle, have only one player and exit,
//and the collectables and exit need to be reachable
bool	valid_map_check(t_map *map)
{
	char	**temp_map;
	bool	check;

	if (!has_player_and_exit(map) || !is_rectangle(map->map, map->width))
		return (false);
	temp_map = map_dup(map->map, map->height);
	if (!temp_map)
		return (false);
	check = flood_fill(temp_map, map->player->position);
	if (!check)
	{
		ft_free_matrix((void ***)&temp_map, map->height);
		return (false);
	}
	check = check_out_of_reach(temp_map);
	ft_free_matrix((void ***)&temp_map, map->height);
	return (check);
}
