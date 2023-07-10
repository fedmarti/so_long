/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:54:22 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/10 22:02:32 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include "../t_point/point.h"

typedef struct s_line
{
	t_point	p1;
	t_point	p2;
}	t_line;

double	line_len(t_line line);

#endif