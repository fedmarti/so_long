/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:43 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/20 17:48:42 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_STRUCTS_H
# define ANIMATION_STRUCTS_H

# include <sys/time.h>
# include "../graphics_logic/graphics_structs.h"

enum e_anim_type{
	Default,
	Looping
};

typedef struct s_anim_frame
{
	t_img_fraction	*img;
	suseconds_t		duration;
}	t_frame;


typedef struct s_animation
{
	char				*name;
	enum e_anim_type	type;
	t_array				frames;
	suseconds_t			tot_duration;
}	t_animation;

typedef struct s_anim_data
{
	t_image			*spritesheet;
	t_image			*current_frame;
	t_animation		*animation;
	t_array			sprites;
}	t_anim_data;


#endif