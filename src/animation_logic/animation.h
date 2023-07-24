/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:23:04 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/23 23:36:02 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include "animation_structs.h"

void		animation_play(char *aniamtion_name, \
				t_anim_data *animation_struct, unsigned short speed);
t_animation	*find_animation_by_name(char *aniamtion_name, \
				t_array *anim_arr, size_t len);
void		read_animation_file(char *filepath, \
				t_anim_data **anim_struct, void *mlx);
void		render_animation(t_anim_data *data, suseconds_t delta_time);

#endif