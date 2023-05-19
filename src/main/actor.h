/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 04:24:25 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/19 05:04:54 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTOR_H
# define ACTOR_H

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
	t_point				velocity;
	t_point				size;
	t_image				*img;
	enum e_tile_type	type;
}	t_actor;

typedef struct s_enemy {
	enum e_enemy_type	type;	
}	t_enemy;



void	actor_free(t_actor	**actor);

#endif