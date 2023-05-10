/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:03:05 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/10 01:06:50 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_STRUCT_H
# define INPUT_STRUCT_H

# include <stdbool.h>

typedef struct s_input
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	space;
	bool	esc;
	bool	shift_left;
	bool	ctrl_left;
}	t_input;
	
#endif