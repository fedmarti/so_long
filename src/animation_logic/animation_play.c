/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_play.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:50:33 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/24 22:14:35 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation_structs.h"

//looks through an animation array and looks for the first animation
// that matches the name passed as a string
//returns NULL if it fails
t_animation	*find_animation_by_name(char *aniamtion_name, t_array *anim_arr, \
									size_t len)
{
	size_t		i;
	t_animation	*current_animation;

	if (len == 0)
		return (NULL);
	i = 0;
	current_animation = anim_arr->arr;
	while (i < anim_arr->n_members)
	{
		if (!ft_strncmp(aniamtion_name, current_animation->name, \
		ft_min((int)len, (int)ft_strlen(current_animation->name))))
			return (current_animation);
		i++;
		current_animation++;
	}
	return (NULL);
}

//sets desired animation as current_animation
//if the name isn't found in the animation array it does nothing
//if the animation is already playing it updates its speed without restarting
//doesn't actually render the animation
void	animation_play(char *aniamtion_name, \
t_anim_data *animation_struct, unsigned short speed)
{
	t_animation	*animation;
	size_t		len;

	len = ft_strlen(aniamtion_name);
	if (animation_struct->current_animation.animation && \
		!ft_strncmp (animation_struct->current_animation.animation->name, \
		aniamtion_name, len))
	{
		animation_struct->current_animation.speed = speed;
		return ;
	}
	animation = \
	find_animation_by_name(aniamtion_name, &animation_struct->animations, len);
	if (!animation)
		return ;
	animation_struct->current_animation.animation = animation;
	animation_struct->current_animation.current_frame = 0;
	animation_struct->current_animation.speed = speed;
	animation_struct->current_animation.time_since_last_frame = 0;
}
