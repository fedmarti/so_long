/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:07:13 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/09 21:14:54 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "map_load.h"

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
	t_point	zero;

	zero.x = 0;
	zero.y = 0;
	return (vector_cmpr(map->player_position, zero) \
	&& vector_cmpr(map->exit_position, zero));
}
