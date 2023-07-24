/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 00:31:38 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/24 22:25:35 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "anime.h"
#include "../code_units/handle_input.h"
#include "../../src/animation_logic/animation.h"

void	mouse_left(t_data *data, t_point pos)
{
	t_data	*d = data;

	if (!ft_strncmp(d->anime->current_animation.animation->name, "run", 3))
		animation_play("amogu", data->anime, 100);
	else
		animation_play("run", data->anime, 50);
	(void)pos;
}

int	on_click(int button, int x, int y, void *data)
{
	t_data *d = data;

	(void)d;
	if (button == 1)
		mouse_left(data, point2(x, y));
	else if (button == 2)
	{
		;
	}
	return (0);
}


void	setup_hooks(t_data *data)
{
	mlx_hook(data->mlx_window, DestroyNotify, 0L, ft_quit, (void *)data);
	// mlx_hook(data->mlx_window, KeyPress, KeyPressMask, on_key_press, (void *)data);
	// mlx_hook(data->mlx_window, KeyRelease, KeyReleaseMask, on_key_release, (void *)data);
	mlx_mouse_hook(data->mlx_window, on_click, (void *)data);
	mlx_loop_hook(data->mlx, ft_process, (void *)data);
}
