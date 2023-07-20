/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:29:58 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/19 17:25:03 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actor_internal.h"
#include "../macro_headers/general_settings.h"
#include "../../so_long.h"
#include "../graphics_logic/graphics.h"

void	*collectable_additional(t_point	position, char *filepath, \
								t_actor *main, t_data *data)
{

	(void)position;
	(void)filepath;
	(void)main;
	(void)data;
	return (NULL);
}

void	*wall_additional(t_point position, char *filepath, \
						t_actor *main, t_data *data)
{
	(void)position;
	(void)filepath;
	(void)main;
	(void)data;
	return (NULL);
}

static t_image	*placeholder_img(t_actor *actor, void *mlx)
{
	unsigned int	color;

	if (actor->type == Wall)
		color = 0x80aec5eb;
	else if (actor->type == Collectable)
		color = 0x50ebd36c;
	else if (actor->type == Exit)
		color = 0x500B00B6;
	else if (actor->type == Enemy)
		color = 0x50FF0000;
	else
		color = 0x694299;
	return (image_init_color(actor->size.x, actor->size.y, mlx, color));
}

//actor->additional_struct = additional(position, filepath, actor);
//actor is passed to potentially edit some type specific characteristics
t_actor	*actor_init(t_point	position, char *filepath, char type, t_data *data)
{
	t_actor	*actor;
	void	*(*additional)(t_point, char *, t_actor *, t_data *);

	if (type == Wall)
		additional = wall_additional;
	else if (type == Enemy)
		additional = enemy_additional;
	else if (type == Collectable)
		additional = collectable_additional;
	else if (type == Player)
		additional = player_additional;
	else if (type == Exit)
		additional = exit_additional;
	else
		return (NULL);
	actor = ft_calloc(1, sizeof(*actor));
	if (!actor)
		return (NULL);
	actor->position = point_multiply(position, TILE_SIZE);
	actor->size = point2(TILE_SIZE, TILE_SIZE);
	actor->type = type;
	actor->additional_struct = additional(position, filepath, actor, data);
	if (!actor->sprite)
		actor->sprite = placeholder_img(actor, data->mlx);
	return (actor);
}
