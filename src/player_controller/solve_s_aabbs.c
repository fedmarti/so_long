/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_s_aabbs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:56:23 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 01:14:10 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"
#include "swept_aabb.h"

bool	is_closer(t_list *node);
t_list	*check_collision_type(struct s_data_pack *data, t_list *collision_list);

static t_list	*sort_collision_list(t_list *lst)
{
	t_list			*temp;
	unsigned int	len;
	unsigned int	j;
	unsigned int	i;

	if (!lst || !lst->next)
		return (lst);
	len = ft_lstlen(lst);
	i = 0;
	while (i < len)
	{
		if (is_closer(lst))
			lst = ft_lst_swap_next(lst);
		temp = lst;
		j = 1;
		while (j < len - i - 1)
		{
			if (!is_closer(temp->next))
				temp->next = ft_lst_swap_next(temp->next);
			temp = temp->next;
			j++;
		}
		i++;
	}
	return (lst);
}

static inline t_vector	get_normal(short mask)
{
	t_vector	vec;

	vec = (t_vector){((mask & 2) >> 1) - ((mask & 8) >> 3), \
		((mask & 4) >> 2) - (mask & 1)};
	if (vec.x && vec.y)
		vec = vector_multiply(vec, 0.70710678118);
	return (vec);
}

static inline short	get_mask(t_vector v)
{
	return (1 * (v.y < 0) \
		| 0b10 * (v.x > 0) \
		| 0b100 * (v.y > 0) \
		| 0b1000 * (v.x < 0));
}

t_vector	get_remaining_velocity(t_vector vel, short mask, \
double collision_time)
{
	short		bit_mask;
	t_vector	normal;
	double		dot_prod;

	bit_mask = 1;
	while (bit_mask <= 8)
	{
		normal = get_normal(mask & bit_mask);
		if (normal.x || normal.y)
		{
			dot_prod = (vel.x * normal.y + vel.y * normal.x) \
			* (1 - collision_time);
			vel = (t_vector){normal.y * dot_prod, normal.x * dot_prod};
		}
		bit_mask <<= 1;
	}
	return (vel);
}

t_vector	solve_s_aabbs(struct s_data_pack *data, t_list **collision_list)
{
	t_list		*list;
	short		normal_mask;
	double		col_tim;

	list = check_collision_type(data, sort_collision_list(*collision_list));
	if (!list)
		return (*data->vel);
	col_tim = ((t_swept_aabb *)list->content)->collision_time;
	normal_mask = get_mask(((t_swept_aabb *)list->content)->normal);
	list = ft_lstnext_and_delete(list, free);
	while (list && (col_tim == ((t_swept_aabb *)list->content)->collision_time))
	{
		normal_mask |= get_mask(((t_swept_aabb *)list->content)->normal);
		list = ft_lstnext_and_delete(list, free);
	}
	data->actor->position = point_add(data->actor->position, \
	vector_to_point(vector_multiply(*data->vel, col_tim)));
	ft_lstclear(&list, free);
	return (get_remaining_velocity(*data->vel, normal_mask, col_tim));
}
