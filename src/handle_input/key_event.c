/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:40:17 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 23:01:54 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_struct.h"
#include "../macro_headers/key_codes.h"
#include "../../so_long.h"

static void	key_event(int key_code, t_input *input, bool press)
{
	if (key_code == ARROW_DOWN_KEY)
		input->down = press;
	else if (key_code == ARROW_LEFT_KEY)
		input->left = press;
	else if (key_code == ARROW_RIGHT_KEY)
		input->right = press;
	else if (key_code == ARROW_UP_KEY)
		input->up = press;
	else if (key_code == SHIFT_LEFT_KEY)
		input->shift_left = press;
	else if (key_code == CTRL_LEFT_KEY)
		input->ctrl_left = press;
	else if (key_code == SPACE_KEY)
		input->space = press;
	else if (key_code == ESC_KEY)
		input->esc = press;
}

int	on_key_press(int key_code, void *data)
{
	key_event(key_code, &(((t_data *)data)->input), true);
	return (1);
}

int	on_key_release(int key_code, void *data)
{
	key_event(key_code, &(((t_data *)data)->input), false);
	return (1);
}
