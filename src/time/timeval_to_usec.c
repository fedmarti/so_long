/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeval_to_usec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:05:00 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/18 22:11:38 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time_structs.h"
#include "ft_time.h"

suseconds_t	timeval_to_usec(struct timeval tv)
{
	return (tv.tv_sec * ONE_SEC + tv.tv_usec);
}

struct timeval usec_to_timeval(suseconds_t val)
{
	return (time_recalibrate((struct timeval){0, val}));
}