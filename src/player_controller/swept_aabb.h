/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swept_aabb.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:07:32 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/27 19:15:59 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWEPT_AABB_H
# define SWEPT_AABB_H

# include "../t_point/t_point_structs.h"
# include "../actor_logic/actor_structs.h"

typedef struct s_swept_aabb
{
	double		collision_time;
	t_vector	normal;
	bool		collision;
}	t_swept_aabb;

t_swept_aabb	swept_aabb(t_actor *actor, t_vector vel, t_actor *target);

#endif