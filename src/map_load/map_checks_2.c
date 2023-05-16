/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:07:13 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/15 18:28:50 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_load_internal.h"

bool	is_rectangle(char **map, unsigned int width)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) != width)
			return (false);
		i++;
	}
	return (true);
}

bool	has_player_and_exit(t_map *map)
{
	if (map->player && map->exit)
		return (true);
	return (false);
}
