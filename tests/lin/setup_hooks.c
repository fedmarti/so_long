/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 00:31:38 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/29 18:05:42 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "../code_units/handle_input.h"

void	mouse_left(t_data *data, t_point pos)
{
	static int			count;
	static t_rectangle	*rec;

	if (count & 1 && rec)
	{
		if (pos.x < rec->pos.x)
		{
			int temp = pos.x;
			pos.x = rec->pos.x;
			rec->pos.x = temp;
		}
		if (pos.y < rec->pos.y)
		{
			int temp = pos.y;
			pos.y = rec->pos.y;
			rec->pos.y = temp;
		}
		rec->size = point_subtract(pos, rec->pos);
		ft_lstclear(&data->raycaster_struct->rec_list, free);
		ft_lstadd_front(&data->raycaster_struct->rec_list, ft_lstnew((void *)rec)); 
	}
	else
	{
		rec = ft_calloc(1, sizeof(*rec));
		if (!rec)
			return ;
		rec->pos = pos;
	}
	count++;
}

void	mouse_right(t_data *data, t_point pos)
{
	static int		count;
	static t_line	*line;

	if (count & 1 && line)
	{
		line->p2 = pos;
		ft_lstadd_front(&data->raycaster_struct->line_list, ft_lstnew((void *)line)); 
	}
	else
	{
		line = ft_calloc(1, sizeof(*line));
		if (!line)
			return ;
		line->p1 = pos;
	}
	count++;
}

int	on_click(int button, int x, int y, void *data)
{
	if (button == 1)
		mouse_left(data, point2(x, y));
	else if (button == 3)
		mouse_right(data, point2(x, y));
	return (0);
}



void	setup_hooks(t_data *data)
{
	mlx_hook(data->mlx_window, DestroyNotify, 0L, ft_quit, (void *)data);
	mlx_hook(data->mlx_window, KeyPress, KeyPressMask, on_key_press, (void *)data);
	mlx_hook(data->mlx_window, KeyRelease, KeyReleaseMask, on_key_release, (void *)data);
	mlx_mouse_hook(data->mlx_window, on_click, (void *)data);
	mlx_loop_hook(data->mlx, ft_process, (void *)data);
}
