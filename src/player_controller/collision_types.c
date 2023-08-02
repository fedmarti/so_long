/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:58:42 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 00:27:40 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"
#include "swept_aabb.h"

t_list	*check_coin_collection(struct s_data_pack *data, t_list *collision_list)
{
	t_swept_aabb	*collision;

	collision = collision_list->content;
	while (collision && collision->target->type == Collectable)
	{
		actor_free(collision->target, data->map, data->data->mlx);
		collision_list = ft_lstnext_and_delete(collision_list, free);
		collision = collision_list->content;
	}
	return (collision_list);
}

t_list	*player_collisions(struct s_data_pack *data, t_list *collision_list)
{
	t_swept_aabb	*collision;

	while (collision_list)
	{
		collision = collision_list->content;
		if ((collision->target->type == Exit && !data->map->collectable_list) \
		|| collision->target->type == Enemy)
		{
			if (collision->target->type == Exit)
				write(1, WIN_MESSAGE, ft_strlen(WIN_MESSAGE));
			ft_lstclear(&collision_list, free);
			actor_free(data->actor, data->map, data->data->mlx);
			ft_quit(data->data);
		}
		else if (collision->target->type == Collectable)
		{
			actor_free(collision->target, data->map, data->data->mlx);
			collision_list = ft_lstnext_and_delete(collision_list, free);
		}
		else
			break ;
	}
	return (collision_list);
}

t_list	*check_collision_type(struct s_data_pack *data, t_list *collision_list)
{
	t_swept_aabb	*collision;

	if (data->actor->type != Player)
	{
		while (collision_list)
		{
			collision = collision_list->content;
			if (collision->target->type == Player && data->actor->type == Enemy)
			{
				ft_lstclear(&collision_list, free);
				actor_free(data->actor, data->map, data->data->mlx);
				ft_quit(data->data);
			}
			else if (collision->target->type != Collectable)
				break ;
			collision_list = ft_lstnext_and_delete(collision_list, free);
		}
		return (collision_list);
	}
	return (player_collisions(data, collision_list));
}
