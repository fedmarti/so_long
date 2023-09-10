/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 00:51:36 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/10 15:31:27 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../graphics_logic/graphics.h"

void	*counter_free(void **counter, void *mlx);

void	free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
		map_free(&data->map);
	if (data->pre_buffer)
		img_free(data->pre_buffer, data->mlx);
	if (data->buffer)
		img_free(data->buffer, data->mlx);
	if (data->mlx_window)
		mlx_destroy_window(data->mlx, data->mlx_window);
	if (data->mlx)
	{
		if (data->counter)
			counter_free(&data->counter, data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
}

//is called when you want to exit the program
//needs to be updated 
int	ft_quit(void *data)
{
	if (((t_data *)data)->mlx)
		mlx_do_key_autorepeaton(((t_data *)data)->mlx);
	free_all((t_data *)data);
	exit(0);
}
