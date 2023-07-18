/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:50:26 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/18 21:26:46 by fedmarti         ###   ########.fr       */
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
	struct timezone	tz;
};


#endif