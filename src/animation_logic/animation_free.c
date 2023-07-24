/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:40:14 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/24 23:38:35 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation_structs.h"
#include "../graphics_logic/graphics.h"

void	array_free(t_array *arr, void (*del)(void *))
{
	size_t i;

	if (!arr || !arr->arr)
		return ;
	if (!del)
	{
		free(arr->arr);
		*arr = (t_array){NULL, 0, 0};
		return ;
	}
	i = 0;
	while (i < arr->n_members)
	{
		del(arr->arr + i * arr->member_size);
		i++;
	}
}

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
	array_free(&(data)->sprites, NULL);
}

static void	ani_free(void *ani)
{
	t_animation *animation;

	animation = ani;
	if (animation->name)
		free(animation->name);
	array_free(&animation->frames, NULL);
}

void	animation_struct_free(t_anim_data **data, void *mlx)
{
	if (!data)
		return ;
	free_speadsheet(*data, mlx);
	(*data)->current_animation = (t_loaded_anim){NULL, 0, 0, 0};
	array_free(&(*data)->animations, ani_free);
	free(*data);
	*data = NULL;
}
