/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_s_aabbs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:54:16 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 00:16:07 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"
#include "swept_aabb.h"

bool	is_in_lst(t_list **list, t_swept_aabb collision)
{
	t_list			*node;
	t_swept_aabb	*temp;

	node = *list;
	while (node)
	{
		temp = node->content;
		if (temp->target == collision.target)
			return (true);
		node = node->next;
	}
	return (false);
}

	// double	collision_time;
	// t_vector	normal;
	// bool		collision;
	// t_actor		*target;

void	get_s_aabbs(t_list *tile_list, t_actor *actor, \
t_vector vel, t_list **entity_list)
{
	t_swept_aabb	result;
	t_swept_aabb	*content;
	t_list			*new_node;

	while (tile_list)
	{
		result = (t_swept_aabb){0.0, (t_vector){0, 0}, false, NULL};
		if (actor != tile_list->content)
			result = swept_aabb(actor, vel, tile_list->content);
		if (result.collision && !is_in_lst(entity_list, result))
		{
			content = malloc(sizeof(*content));
			if (!content)
				break ;
			*content = result;
			new_node = ft_lstnew(content);
			if (!new_node)
			{
				free(content);
				break ;
			}
			ft_lstadd_back(entity_list, new_node);
		}
		tile_list = tile_list->next;
	}
}
