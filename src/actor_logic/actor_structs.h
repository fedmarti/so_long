/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 04:24:25 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 22:56:35 by fedmarti         ###   ########.fr       */
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
	Null = 0
};

typedef struct s_actor {
	void				*additional_struct;
	t_point				position;
	t_vector			sub_pixel_pos;
	t_vector			velocity;
	t_point				size;
	t_image				*sprite;
	enum e_tile_type	type;
}	t_actor;

typedef struct s_enemy {
	enum e_enemy_type	type;	
}	t_enemy;

#endif