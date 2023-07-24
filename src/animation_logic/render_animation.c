/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:32:53 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/24 02:17:06 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation_structs.h"
#include "../time/ft_time.h"

static unsigned short	get_current_frame(t_loaded_anim current_animation, \
					suseconds_t *time_elapsed)
{
	unsigned short	i;
	t_frame			*frame_arr;
	unsigned short	arr_len;
	double			speed;

	i = current_animation.current_frame;
	frame_arr = current_animation.animation->frames.arr;
	arr_len = current_animation.animation->frames.n_members;
	speed = (double)current_animation.speed / 100;
	while (i < arr_len - 1 \
	&& *time_elapsed > (suseconds_t)((double)frame_arr[i].duration / speed))
	{
		*time_elapsed -= (suseconds_t)((double)frame_arr[i].duration / speed);
		i++;
		if (current_animation.animation->type == Looping && i >= arr_len - 1)
			i = 0;
	}
	return (i);
}

void	render_animation(t_anim_data *data, suseconds_t delta_time)
{
	suseconds_t		time_elapsed;
	unsigned short	current_frame;

	if (!data || !data->current_animation.animation)
		return ;
	time_elapsed = data->current_animation.time_since_last_frame;
	current_frame = get_current_frame(data->current_animation, &time_elapsed);
	if (data->current_animation.current_frame != current_frame)
	{
		data->current_animation.current_frame = current_frame;
		data->current_animation.time_since_last_frame = time_elapsed;
	}
	if (data->current_animation.current_frame != \
	data->current_animation.animation->frames.n_members - 1)
		data->current_animation.time_since_last_frame += delta_time;
	data->current_frame = ((t_frame *)data->current_animation.\
	animation->frames.arr)[current_frame].img;
}
