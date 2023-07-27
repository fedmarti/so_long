/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_settings.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:00:42 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/27 19:24:21 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_SETTINGS_H
# define GENERAL_SETTINGS_H

//previously 256
# ifndef BASE_SCREEN_WIDTH
#  define BASE_SCREEN_WIDTH 304
# endif

//previously 224
# ifndef BASE_SCREEN_HEIGHT
#  define BASE_SCREEN_HEIGHT 176
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 16
# endif

# ifndef ANIMATION_HEADER
#  define ANIMATION_HEADER "Animation data file\n"
# endif

# ifndef PLAYER_SPEED
#  define PLAYER_SPEED 23
# endif

# ifndef DASH_BOOST
#  define DASH_BOOST PLAYER_SPEED * 2
# endif

# ifndef GRAVITY
#  define GRAVITY 35
# endif 

# ifndef JUMP
#  define JUMP 1.125
# endif 

# ifndef FRAME_TIME
#  define FRAME_TIME 16666l
# endif

#endif

