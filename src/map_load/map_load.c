/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:42:34 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/02 23:15:38 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_load.h"

t_list	*map_read(char *filepath)
{
	int		fd;
	t_list	*head;
	t_list	*temp;
	char	*temp_str;

	fd = open(filepath, 'r');
	if (fd <= 0)
		return (NULL);
	head = NULL;
	temp_str = get_next_line(fd);
	while (temp_str)
	{
		temp = ft_lstnew(temp_str);
		if (!temp)
		{
			ft_lstclear(&head, free);
			close(fd);
			return (NULL);
		}
		ft_lstadd_back(&head, temp);
		temp_str = get_next_line(fd);
	}
	close (fd);
	return (head);
}

t_map	*map_fill(t_map *map, t_list *row_list)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < map->height)
	{
		map->map[y] = (char *)row_list->content;
		x = 0;
		while (map->map[y][x])
		{
			if (check_tile(map, map->map[y][x], vector2(x, y)))
				return (NULL);
			x++;
		}
	}
}

t_map	*map_init(t_list *row_list)
{
	t_map	*map;

	map = malloc(sizeof(*map));
	if (!map)
		return (NULL);
	map->width = (unsigned int) ft_strlen((char *)row_list->content);
	map->height = (unsigned int) ft_lslen(row_list);
	map->player_position = vector2(0, 0);
	map->exit_position = vector2(0, 0);
	map->entity_list = NULL;
	map->collectable_list = NULL;
	map->object_list = NULL;
	map = map_fill(map, row_list);
	return (map);
}

t_map	*map_load(char *filepath)
{
	t_list	*row_list;
	t_map	*map;

	row_list = map_load(filepath);
	if (!row_list)
		return (NULL);
	map = map_init(row_list);
	ft_lstclear(&row_list, ft_do_nothing);
	return (map);
}
