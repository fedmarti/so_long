/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:13:50 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/10 01:34:32 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../graphics_logic/graphics.h"

int	ft_process(void *data)
{
	//enemy_logic()
	player_controller(data);
	render_frame(data);
	return (0);
}
