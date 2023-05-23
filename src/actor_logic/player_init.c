/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:10:35 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/23 01:29:55 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actor_internal.h"

void	*player_additional(t_point position, char *filepath, \
							t_actor *main, t_data *data)
{
	(void)position;
	(void)filepath;
	(void)main;
	(void)data;
	return (NULL);
}
