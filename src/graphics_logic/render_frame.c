/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:34:53 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/12 20:33:55 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	render_frame(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_window);
	mlx_put_image_to_window(data->mlx, data->mlx_window, data->img->img, \
	(data->pos).x, (data->pos).y);
}
