/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_to_rectangle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:29:20 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/17 21:01:25 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static inline void	get_lines(t_line *lines, t_point rec_pos, t_point rec_size)
{
	lines[0] = (t_line){rec_pos, (t_point){rec_pos.x + rec_size.x, rec_pos.y}};
	lines[1] = (t_line)\
	{(t_point){rec_pos.x + rec_size.x, rec_pos.y}, \
	(t_point){rec_pos.x + rec_size.x, rec_pos.y + rec_size.y}};
	lines[2] = (t_line)\
	{(t_point){rec_pos.x + rec_size.x, rec_pos.y + rec_size.y},\
	(t_point){rec_pos.x, rec_pos.y + rec_size.y}};
	lines[3] = (t_line){{rec_pos.x, rec_pos.y + rec_size.y}, rec_pos};
}

struct s_hit	\
raycast_to_rectangle \
(t_point from, t_point to, t_point rec_pos, t_point rec_size)
{
	t_line	lines[4];
	t_hit	hit;
	t_hit	temp;
	int		i;

	hit = (t_hit){(t_point){0,0}, (t_point){0,0}, false};
	get_lines(lines, rec_pos, rec_size);
	i = 0;
	while (i < 4)
	{
		temp = raycast(from, to, lines[i].p1, lines[i].p2);
		// if (temp.collision && (!hit.collision 
		// || line_len((t_line){from, hit.intersection}) 
		// > line_len((t_line){from, temp.intersection})))
		if (is_h2_closer(hit, temp))
			hit = temp;
		i++;
	}
	return (hit);
}

t_hit	rec_shoot_ray(t_rectangle actor, \
t_point direction_vector, t_rectangle target)
{
	t_hit		hit;
	t_rectangle	big_rec;
	t_point		starting_point;
	
	big_rec.pos = point_subtract(target.pos, point_multiply(actor.size, 0.5));
	big_rec.size = point_add(actor.size, target.size);
	starting_point = point_add(actor.pos, point_multiply(actor.size, 0.5));
	hit = raycast_to_rectangle(starting_point, point_add(starting_point,\
	direction_vector), big_rec.pos, big_rec.size);
	return (hit);
}
