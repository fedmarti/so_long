/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 00:51:36 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/12 19:02:57 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"




void	free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
		map_free(&data->map);
	if (data->img->img)
		mlx_destroy_image(data->mlx, data->img->img);
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