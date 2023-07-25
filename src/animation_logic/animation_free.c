/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:40:14 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/25 18:28:29 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation_structs.h"
#include "../graphics_logic/graphics.h"

void	*animation_free(t_animation **animation)
{
	if (!*animation)
		return (NULL);
	if ((*animation)->name)
		free((*animation)->name);
	if ((*animation)->frames.arr)
		free((*animation)->frames.arr);
	free(*animation);
	*animation = NULL;
	return (NULL);
}

void	free_speadsheet(t_anim_data *data, void *mlx)
{
	if (data->spritesheet && mlx)
	{
		img_free(data->spritesheet, mlx);
		data->spritesheet = NULL;
	}
	ft_array_free(&(data)->sprites, NULL);
}

void	frame_free(void *f)
{
	t_frame	*frame;

	frame = f;
	if (frame && frame->img)
		free(frame->img);	
}

static void	ani_free(void *ani)
{
	t_animation *animation;

	animation = ani;
	if (animation->name)
		free(animation->name);
	ft_array_free(&animation->frames, NULL);
}

void	animation_struct_free(t_anim_data **data, void *mlx)
{
	if (!data)
		return ;
	free_speadsheet(*data, mlx);
	(*data)->current_animation = (t_loaded_anim){NULL, 0, 0, 0};
	ft_array_free(&(*data)->animations, ani_free);
	free(*data);
	*data = NULL;
}
