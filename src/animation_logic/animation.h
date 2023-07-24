/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:23:04 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/24 23:04:50 by fedmarti         ###   ########.fr       */
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
void		*animation_free(t_animation **animation);
void		animation_struct_free(t_anim_data **data, void *mlx);
void		free_speadsheet(t_anim_data *data, void *mlx);

#endif