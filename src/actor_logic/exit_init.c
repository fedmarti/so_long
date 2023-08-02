/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:09:24 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 22:52:24 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actor_internal.h"

#include <stdbool.h>

void	*exit_additional(t_point position, char *filepath, \
						t_actor *main, t_data *data)
{
	(void)data;
	(void)position;
	(void)filepath;
	(void)main;
	return (NULL);
}
