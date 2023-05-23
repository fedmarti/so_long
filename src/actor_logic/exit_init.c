/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:09:24 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/23 01:29:29 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actor_internal.h"

#include <stdbool.h>

void	*exit_additional(t_point position, char *filepath, \
						t_actor *main, t_data *data)
{
	bool	*open;

	(void)data;
	main->size = point_subtract(main->size, point2(-2, -1));
	open = ft_calloc(1, sizeof(bool *));
	(void)position;
	(void)filepath;
	(void)main;
	return (open);
}
