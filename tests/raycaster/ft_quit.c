/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 00:51:36 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/20 18:13:18 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "../code_units/graphics_logic.h"


void	free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->pre_buffer)
		img_free(data->pre_buffer, data->mlx);
	if (data->buffer)
		img_free(data->buffer, data->mlx);
	if (data->mlx_window)
		mlx_destroy_window(data->mlx, data->mlx_window);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
}

//is called when you want to exit the program
//needs to be updated 
int	ft_quit(void *data)
{
	free_all((t_data *)data);
	exit(0);
}
