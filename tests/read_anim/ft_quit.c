/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 00:51:36 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/24 23:16:02 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "anime.h"
#include "../code_units/graphics_logic.h"

void		animation_struct_free(t_anim_data **data, void *mlx);

void	free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->pre_buffer)
		img_free(data->pre_buffer, data->mlx);
	if (data->buffer)
		img_free(data->buffer, data->mlx);
	if (data->anime)
		animation_struct_free(&data->anime, data->mlx);
	if (data->time)
	{
		free(data->time);
		data->time = NULL;
	}
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
