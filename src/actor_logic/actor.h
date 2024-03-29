/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:47:56 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 18:21:01 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTOR_H
# define ACTOR_H

# include "actor_structs.h"

void	actor_free(t_actor *actor, t_map *map, void *mlx);
t_actor	*actor_init(t_point	position, char *filepath, char type, t_data *data);

#endif