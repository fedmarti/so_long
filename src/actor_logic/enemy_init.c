/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:11:59 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 22:56:56 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actor_internal.h"
#include "../graphics_logic/graphics.h"

void	enemy_free(void *enemy, void *mlx)
{
	t_actor	*en;

	(void)mlx;
	en = (t_actor *)enemy;
	if (!enemy)
		return ;
	if (en->additional_struct)
		free(en->additional_struct);
	free(en);
}

void	*enemy_additional(t_point position, char *filepath, \
						t_actor *main, t_data *data)
{
	t_enemy	*enemy_characteristics;

	(void)data;
	enemy_characteristics = ft_calloc(1, sizeof(*enemy_characteristics));
	if (!enemy_characteristics)
		return (NULL);
	enemy_characteristics->type = Null;
	(void)position;
	(void)filepath;
	(void)main;
	return (enemy_characteristics);
}
