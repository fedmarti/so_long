/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 04:24:25 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/06 19:56:16 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTOR_STRUCTS_H
# define ACTOR_STRUCTS_H

# include "../t_point/point.h"
# include "../graphics_logic/graphics_structs.h"

enum e_tile_type {
	Player = 'P',
	Wall = '#',
	Exit = 'E',
	Empty = ' ',
	Enemy = 'X',
	Collectable = 'C',
	Void = '\0'
};

enum e_enemy_type {
	Zombie = 1,
	Default = 0
};

typedef struct s_actor {
	void				*additional_struct;
	t_point				position;
	t_vector			sub_pixel_pos;
	t_point				velocity;
	t_point				size;
	t_image				*sprites;
	enum e_tile_type	type;
}	t_actor;

typedef struct s_enemy {
	enum e_enemy_type	type;	
}	t_enemy;

#endif