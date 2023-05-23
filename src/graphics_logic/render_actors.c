/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_actors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:16:24 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/23 19:41:56 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics_logic/graphics.h"
#include "../../libft_plus/libft_plus.h"
#include "graphics_internal.h"

t_list	*get_actor_list(t_map *map, t_point pos, t_point area_size)
{
	t_list	*actor_list;
	t_list	*temp_list;
	t_point	i;

	i.y = pos.y;
	actor_list = NULL;
	while (i.y < area_size.y)
	{
		i.x = pos.x;
		while (i.x < area_size.x)
		{
			temp_list = map->tiles[i.y][i.x].entity_list;
			while (temp_list)
			{
				if (!ft_is_in_list \
				(actor_list, temp_list->content, sizeof(t_actor)))
					ft_lstadd_back(&actor_list, ft_lstnew(temp_list->content));
				temp_list = temp_list->next;
			}
			i.x++;
		}
		i.y++;
	}
	return (actor_list);
}

void	render_enemy(t_actor *enemy, t_data *data)
{
	(void)enemy;
	(void)data;
}

void	render_void(t_actor *enemy, t_data *data)
{
	(void)enemy;
	(void)data;
}

void	(*get_rendering_function(char type))
(t_actor *, t_data *)
{
	if (type == Enemy)
		return (&render_enemy);
	else
		return (&render_void);
	//inCumplete
}

void	render_actor(void *a, void *d)
{
	t_actor	*actor;
	t_data	*data;

	actor = (t_actor *)a;
	data = (t_data *)d;
	blend_images(actor->sprites, data->pre_buffer, actor->position, overlay);
}


t_image	*render_actors(t_data *data)
{
	t_list	*actor_list;

	actor_list = get_actor_list(data->map, point2(0, 0), \
				point2((int) data->map->width, (int) data->map->height));
	ft_lst_iteri_2(actor_list, render_actor, data);
	ft_lstclear(&actor_list, ft_do_nothing);
	return (data->pre_buffer);
}
