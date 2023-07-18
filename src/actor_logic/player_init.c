/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:10:35 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/18 20:14:16 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actor_internal.h"
#include "../graphics_logic/graphics.h"
#include "../../libft/libft.h"

void	*player_additional(t_point position, char *filepath, \
							t_actor *main, t_data *data)
{
	// main->sprites = sprit
	main->sprites = ft_calloc(1, sizeof(*main->sprites));
	main->sprites = image_init_xpm(main->sprites, PLAYER_SPRITES, data->mlx);
	main->sprites->offset = point2(-7, -8);
	// main->size = point2(TILE_SIZE - 1, TILE_SIZE - 1);
	(void)position;
	(void)filepath;
	(void)main;
	(void)data;
	return (NULL);
}
