/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:21:23 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 00:22:19 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swept_aabb.h"
#include "../../libft/libft.h"

bool	is_closer(t_list *node)
{
	return (((t_swept_aabb *)node->content)->collision_time \
	> (((t_swept_aabb *)node->next->content)->collision_time));
}
