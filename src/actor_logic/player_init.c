/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:10:35 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 22:51:12 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actor_internal.h"
#include "../graphics_logic/graphics.h"
#include "../../libft/libft.h"

void	*player_additional(t_point position, char *filepath, \
							t_actor *main, t_data *data)
{
	main->sprite = ft_calloc(1, sizeof(*main->sprite));
	main->sprite = image_init_xpm(main->sprite, PLAYER_SPRITES, data->mlx);
	main->sprite->offset = point2(-7, -8);
	main->size = point2(TILE_SIZE - 1, TILE_SIZE - 1);
	(void)position;
	(void)filepath;
	(void)main;
	(void)data;
	return (NULL);
}
