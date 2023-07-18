/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:25 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/18 22:16:42 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "../macro_headers/general_settings.h"

void	time_update(struct s_time *time)
{
	
	if ((!time->last_frame.tv_usec && !time->last_frame.tv_sec) \
	&& (!time->this_frame.tv_usec && !time->this_frame.tv_sec))
	{
		gettimeofday(&time->last_frame, (void *)0);
		time->delta = FRAME_TIME;
	}
	else if ((time->last_frame.tv_usec || time->last_frame.tv_sec) \
	&& (!time->this_frame.tv_usec && !time->this_frame.tv_sec))
	{
		gettimeofday(&time->this_frame, (void *)0);
		time->delta = FRAME_TIME;
	}
	else
	{
		time->delta = timeval_to_usec(\
		time_subtract(time->this_frame, time->last_frame));
		time->last_frame = time->this_frame;
		gettimeofday(&time->this_frame, (void *)0);
	}
}
