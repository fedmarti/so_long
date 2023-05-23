/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:03:06 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/23 01:28:10 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTOR_INTERNAL_H
# define ACTOR_INTERNAL_H

# include "actor_structs.h"
# include "../../so_long.h"
# include <stdlib.h>

//setting placeholder sprites, hopefully these get overwritten by another header
# ifndef PLAYER_SPRITES
#  define PLAYER_SPRITES "./media/player/idle_front \
./media/player/idle_back.xpm \
./media/player/idle_left \
./media/player/idle_right"
# endif

# ifndef WALL_SPRITES
#  define WALL_SPRITES NULL
# endif

# ifndef ENEMY_SPRITES
#  define ENEMY_SPRITES NULL
# endif

# ifndef COLLECTABLE_SPRITES
#  define COLLECTABLE_SPRITES NULL
# endif

# ifndef EXIT_SPRITES
#  define EXIT_SPRITES NULL
# endif

void	actor_free(t_actor	**actor);
void		*enemy_additional(t_point position, char *filepath, \
									t_actor *main, t_data *data);
void		*collectable_additional(t_point	position, char *filepath, \
									t_actor *main, t_data *data);
void		*wall_additional(t_point position, char *filepath, \
									t_actor *main, t_data *data);
void		*player_additional(t_point position, char *filepath, \
									t_actor *main, t_data *data);
void		*exit_additional(t_point position, char *filepath, \
									t_actor *main, t_data *data);


#endif