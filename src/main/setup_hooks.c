/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 00:31:38 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 23:17:02 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../handle_input/input.h"

void	setup_hooks(t_data *data)
{
	mlx_hook(data->mlx_window, DestroyNotify, 0L, ft_quit, (void *)data);
	mlx_hook(data->mlx_window, KeyPress, KeyPressMask, \
	on_key_press, (void *)data);
	mlx_hook(data->mlx_window, KeyRelease, KeyReleaseMask, \
	on_key_release, (void *)data);
	mlx_loop_hook(data->mlx, ft_process, (void *)data);
}
