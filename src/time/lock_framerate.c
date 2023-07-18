/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_framerate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:39:54 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/18 22:19:54 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "../macro_headers/general_settings.h"

void	lock_framerate(struct timeval last_frame)
{
	struct timeval time;

	gettimeofday(&time, (void *)0);
	while (timeval_to_usec(time_subtract(time, last_frame)) < FRAME_TIME)
		gettimeofday(&time, (void *)0);
}