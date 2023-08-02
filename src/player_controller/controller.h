/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:43:46 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 23:39:14 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLLER_H
# define CONTROLLER_H

# include "../../so_long.h"

struct s_data_pack
{
	t_point		area_size;
	t_actor		*actor;
	t_vector	*vel;
	t_point		last_gba;
	t_map		*map;
	t_data		*data;
};

void	player_controller(t_data *data);
bool	is_on_ground(t_actor *actor, t_map *map);

#endif