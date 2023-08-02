/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:01:13 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 23:28:24 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H

# include "time_structs.h"

void			time_update(struct s_time *time);
struct timeval	time_recalibrate(struct timeval tv);
struct timeval	time_subtract(struct timeval tv1, struct timeval tv2);
suseconds_t		timeval_to_usec(struct timeval tv);
struct timeval	usec_to_timeval(suseconds_t val);
void			lock_framerate(struct timeval last_frame);

#endif