/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:50:26 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 23:27:54 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_STRUCTS_H
# define TIME_STRUCTS_H

# include <sys/time.h>

# ifndef ONE_SEC
#  define ONE_SEC 1000000
# endif

struct s_time{
	suseconds_t		delta;
	struct timeval	last_frame;
	struct timeval	this_frame;
};

#endif