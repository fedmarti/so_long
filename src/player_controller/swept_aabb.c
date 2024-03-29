/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swept_aabb_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:49:59 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 01:08:25 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "float.h"
#include "../macro_headers/general_settings.h"
#include "../graphics_logic/graphics.h"
#include "swept_aabb.h"

typedef struct s_entry_exit
{
	t_vector	entry;
	t_vector	exit;
}	t_entry_exit;

static t_entry_exit	get_inv_entry_exit(t_actor *actor, \
t_vector vel, t_actor *target)
{
	t_vector	inv_entry;
	t_vector	inv_exit;

	inv_entry.x = (target->position.x + target->size.x) - actor->position.x;
	inv_exit.x = (target->position.x - (actor->position.x + actor->size.x));
	if (vel.x > 0.0 || (vel.x == 0 && inv_entry.x > 0 && inv_exit.x < 0))
		ft_swap_d(&inv_exit.x, &inv_entry.x);
	inv_entry.y = (target->position.y + target->size.y) - actor->position.y;
	inv_exit.y = (target->position.y - (actor->position.y + actor->size.y));
	if (vel.y > 0.0 || (vel.y == 0 && inv_entry.y > 0 && inv_exit.y < 0))
		ft_swap_d(&inv_exit.y, &inv_entry.y);
	return ((t_entry_exit){inv_entry, inv_exit});
}

static inline void	get_x_vals(double *entryx, double *exitx, \
t_vector entry_ex, double velx)
{
	if (!velx)
	{
		if (entry_ex.x < entry_ex.y)
		{
			*entryx = -DBL_MAX;
			*exitx = DBL_MAX;
		}
		else
		{
			*entryx = DBL_MAX;
			*exitx = -DBL_MAX;
		}
	}
	else
	{
		*entryx = entry_ex.x / velx;
		*exitx = entry_ex.y / velx;
	}
}

static t_entry_exit	get_entry_exit(t_vector inv_entry, \
t_vector inv_exit, t_vector vel)
{
	t_vector	entry;
	t_vector	exit;

	get_x_vals(&entry.x, &exit.x, (t_vector){inv_entry.x, inv_exit.x}, vel.x);
	if (!vel.y)
	{
		if (inv_entry.y < inv_exit.y)
		{
			entry.y = -DBL_MAX;
			exit.y = DBL_MAX;
		}
		else
		{
			entry.y = DBL_MAX;
			exit.y = -DBL_MAX;
		}
	}
	else
	{
		entry.y = inv_entry.y / vel.y;
		exit.y = inv_exit.y / vel.y;
	}
	return ((t_entry_exit){entry, exit});
}

	// double		collision_time;
	// t_vector	normal;
	// bool		collision;
	// t_actor		*target;

t_swept_aabb	swept_aabb(t_actor *actor, t_vector vel, t_actor *target)
{
	t_swept_aabb	s_aabb;
	t_entry_exit	inv;
	t_entry_exit	regular;
	double			entry_time;
	double			exit_time;

	s_aabb = (t_swept_aabb){0, (t_vector){0, 0}, false, target};
	inv = get_inv_entry_exit(actor, vel, target);
	regular = get_entry_exit(inv.entry, inv.exit, vel);
	entry_time = ft_max_d(regular.entry.x, regular.entry.y);
	exit_time = ft_min_d(regular.exit.x, regular.exit.y);
	if (entry_time > exit_time || (regular.entry.x < 0 && regular.entry.y < 0) \
	|| regular.entry.x > 1 || regular.entry.y > 1)
		return (s_aabb);
	s_aabb.normal.x = (regular.entry.x > regular.entry.y) * \
	-(ft_sign_d(inv.entry.x) + (!inv.entry.x));
	s_aabb.normal.y = (regular.entry.x <= regular.entry.y) * \
	-(ft_sign_d(inv.entry.y) + (!inv.entry.y));
	s_aabb.collision = true;
	s_aabb.collision_time = entry_time;
	return (s_aabb);
}
