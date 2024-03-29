/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:42:34 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/30 17:36:27 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_load_internal.h"
#include "../../libft/libft.h"
#include "../../so_long.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_map	*map_free(t_map **map)
{
	if (!map || !*map)
		return (NULL);
	ft_free_matrix((void ***)&(*map)->map, (*map)->height);
	free_tiles(*map);
	ft_lstclear(&(*map)->enemy_list, NULL);
	ft_lstclear(&(*map)->object_list, NULL);
	ft_lstclear(&(*map)->collectable_list, NULL);
	ft_lstclear(&(*map)->entity_list, NULL);
	free(*map);
	*map = NULL;
	return (NULL);
}

//uses gnl to create a list containing a line of the map file in each node
t_list	*map_read(char *filepath)
{
	int		fd;
	t_list	*head;
	t_list	*temp;
	char	*temp_str;

	fd = open(filepath, O_RDONLY);
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
	while (y < map->height && row_list)
	{
		map->map[y] = (char *)row_list->content;
		x = 0;
		while (x < map->width)
		{
			if (check_tile(map, map->map[y][x], point2(x, y)))
			{
				ft_lstclear(&row_list->next, free);
				return (map_free(&map));
			}
			x++;
		}
		if (x > 0 && map->map[y][x] == '\n')
			map->map[y][x] = 0;
		y++;
		row_list = row_list->next;
	}
	return (map);
}

t_map	*map_init(t_list *row_list, char *filepath, t_data *data)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(*map));
	if (!map)
		return (NULL);
	map->data = data;
	map->width = (unsigned int) ft_strlen((char *)row_list->content) - 1;
	map->height = (unsigned int) ft_lstlen(row_list);
	map->map_path = filepath;
	map->map = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->map)
		return (map_free(&map));
	map->tiles = (t_tile **)ft_matrix_init(map->width, \
	map->height, sizeof(t_tile));
	if (!map->tiles)
		return (map_free(&map));
	map = map_fill(map, row_list);
	return (map);
}

t_map	*map_load(char *filepath, t_data *data)
{
	t_list	*row_list;
	t_map	*map;

	row_list = map_read(filepath);
	if (!row_list)
		return (NULL);
	map = map_init(row_list, filepath, data);
	ft_lstclear(&row_list, ft_do_nothing);
	if (!map || !valid_map_check(map))
		return (map_free(&map));
	return (map);
}
