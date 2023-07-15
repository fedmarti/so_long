/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:03:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/15 19:25:08 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void \
	draw_line_gba(t_image *img, t_point start, t_point end, unsigned int color);


//only works with squares so far
// AABB collision
bool	is_colliding(t_rectangle *actor1, t_vector vel, t_rectangle *actor2)
{
	t_point	pos_after_movement;


	// rect1.x < rect2.x + rect2.w &&
    // rect1.x + rect1.w > rect2.x &&
    // rect1.y < rect2.y + rect2.h &&
    // rect1.h + rect1.y > rect2.y
	if (actor1 == actor2)
		return (false);
	pos_after_movement = point_add(actor1->pos, vector_to_point(vel));
	return (pos_after_movement.x < actor2->pos.x + actor2->size.x
		&& pos_after_movement.x + actor1->size.x > actor2->pos.x
		&& pos_after_movement.y < actor2->pos.y + actor2->size.y
		&& pos_after_movement.y + actor1->size.y > actor2->pos.y);
}

double	solve_collision_x(t_rectangle *actor1, double vel, t_rectangle *actor2)
{
	double	displacement;
	int		pos_after_movement;
	double	old_vel;

	old_vel = vel;
	pos_after_movement = actor1->pos.x + (int)vel;
	displacement = 0;
	if (vel > 0 && actor1->pos.x < actor2->pos.x)
		displacement = -1 * (pos_after_movement + actor1->size.x - actor2->pos.x);
	else if (vel < 0 && actor1->pos.x > actor2->pos.x)
		displacement = actor2->pos.x + actor2->size.x - pos_after_movement;
	return ((double)ft_abs_clamp_d((vel + (double)displacement), 0, old_vel));
}

double	solve_collision_y(t_rectangle *actor1, double vel, t_rectangle *actor2)
{
	int		displacement;
	int		pos_after_movement;
	double	old_vel;

	old_vel = vel;
	pos_after_movement = actor1->pos.y + (int)vel;
	displacement = 0;
	if (vel > 0 && actor1->pos.y < actor2->pos.y)
		displacement = -1 * (pos_after_movement + actor1->size.y - actor2->pos.y);
	else if (vel < 0 && actor1->pos.y > actor2->pos.y)
		displacement = actor2->pos.y + actor2->size.y - pos_after_movement;
	return ((double)ft_abs_clamp_d((vel + (double)displacement), 0, old_vel));
}

t_vector	solve_collision(t_rectangle *actor1, t_vector vel, t_rectangle *actor2)
{
	if (vel.y && !is_colliding(actor1, vector2(vel.x, 0), actor2))
		vel.y = solve_collision_y(actor1, vel.y, actor2);
	else if (vel.x && !is_colliding(actor1, vector2(0, vel.y), actor2))
		vel.x = solve_collision_x(actor1, vel.x, actor2);
	else
	{
		vel.y = solve_collision_y(actor1, vel.y, actor2);
		vel.x = solve_collision_x(actor1, vel.x, actor2);
	}
			// 	velocity.x = solve_collision_x(actor, velocity.x, (t_actor *)entity_list->content);
	// t_vector	displacement;
	// t_point		pos_after_movement;

	// pos_after_movement = point_add(actor1->position, vector_to_point(vel));
	// displacement = vector2(0 , 0);
	
	// if (vel.x > 0 && actor1->position.x < actor2->position.x)
	// 	displacement.x = -1 * (pos_after_movement.x + actor1->size.x - actor2->position.x);
	// else if (vel.x < 0 && actor1->position.x > actor2->position.x)
	// 	displacement.x = actor2->position.x + actor2->size.x - pos_after_movement.x;

	// if (vel.y > 0 && actor1->position.y < actor2->position.y)
	// 	displacement.y = -1 * (pos_after_movement.y + actor1->size.y - actor2->position.y);
	// else if (vel.y < 0 && actor1->position.y > actor2->position.y)
	// 	displacement.y = actor2->position.y + actor2->size.y - pos_after_movement.y;
	// vel.x = solve_collision_x(actor1, vel.x, actor2);
	// vel.y = solve_collision_y(actor1, vel.y, actor2);
	return (vel);
}

\


void	get_starting_points(t_point *sp, t_point dir, t_rectangle *actor)
{
	sp[0] = actor->pos;
	sp[1] = point_add(actor->pos, point_multiply(actor->size, 0.5));
	sp[2] = point_add(actor->pos, actor->size);
	sp[1].x += actor->size.x * 0.5 * ft_sign(dir.x);
	sp[1].y += actor->size.y * 0.5 * ft_sign(dir.y);
	if (ft_sign(dir.x) == ft_sign(dir.y))
	{
		sp[0].y += actor->size.y;
		sp[2].y -= actor->size.y;
	}
	if (!dir.x && dir.y)
		sp[2 * (dir.y < 0)].y += actor->size.y * ft_sign(dir.y);
	else if (!dir.y && dir.x)
		sp[2 * (dir.x < 0)].x += actor->size.x * ft_sign(dir.x);
}

t_hit	rec_shoot_rays(t_rectangle *actor, t_point direction_vector, t_rectangle *target)
{
	t_hit	hit;
	t_hit	temp_hit;
	t_point	starting_point[3];
	
	get_starting_points(starting_point, direction_vector, actor);
	hit = raycast_to_rectangle(starting_point[0], point_add(starting_point[0],\
	direction_vector), target->pos, target->size);
	temp_hit = raycast_to_rectangle(starting_point[1], point_add\
	(starting_point[1], direction_vector), target->pos, target->size);
	if (is_h2_closer(hit, temp_hit))
		hit = temp_hit;
	temp_hit = raycast_to_rectangle(starting_point[2], point_add\
	(starting_point[2], direction_vector), target->pos, target->size);
	if (is_h2_closer(hit, temp_hit))
		hit = temp_hit;
	return (hit);
}

t_rectangle	*get_colliding_actor(t_list *entity_list, t_rectangle *actor, t_vector vel)
{
	t_list	*temp_node;
	t_hit	hit;
	t_hit	temp_hit;
	t_rectangle	*ca;
	t_rectangle	*temp_actor;

	ca = NULL;
	temp_actor = NULL;
	hit = (t_hit){(t_point){0,0}, (t_point){0,0}, false};
	while (entity_list)
	{
		temp_actor = entity_list->content;
		temp_hit = rec_shoot_rays(actor, vector_to_point(vel), (t_rectangle *)entity_list->content);
		if (is_h2_closer(hit, temp_hit))
		{
			ca = temp_actor;
			hit = temp_hit;
		}
		temp_node = entity_list->next;
		entity_list = temp_node;
	}
	return (ca);
}

void	draw_rays(t_rectangle rec, t_point velocity, t_rectangle *target, t_data *data)
{
	t_hit	hit;
	t_hit	temp_hit;
	t_point	starting_point[3];
	
	get_starting_points(starting_point, velocity, &rec);
	if (!target)
	{
		for (int i = 0; i < 3; i++)
			draw_line_gba(data->buffer, starting_point[i], point_add(starting_point[i], velocity), 0xFFFFFF);
		return ;
	}
	hit = raycast_to_rectangle(starting_point[0], point_add(starting_point[0],\
	velocity), target->pos, target->size);
	temp_hit = raycast_to_rectangle(starting_point[1], point_add\
	(starting_point[1], velocity), target->pos, target->size);
	if (is_h2_closer(hit, temp_hit))
	{
		draw_line_gba(data->buffer, hit.origin, hit.intersection, 0x00ffffff);
		hit = temp_hit;
	}
	else 
		draw_line_gba(data->buffer, temp_hit.origin, temp_hit.intersection, 0x00ffffff);	
	temp_hit = raycast_to_rectangle(starting_point[2], point_add\
	(starting_point[2], velocity), target->pos, target->size);
	if (is_h2_closer(hit, temp_hit))
	{
		draw_line_gba(data->buffer, hit.origin, hit.intersection, 0x00ffffff);
		hit = temp_hit;
	}
	else 
		draw_line_gba(data->buffer, temp_hit.origin, temp_hit.intersection, 0x00ffffff);	
	draw_line_gba(data->buffer, hit.origin, hit.intersection, 0x30ff0000);
}

void	draw_rec(t_rectangle rec, t_image *img, unsigned int color);

void	move_and_collide(t_rectangle *actor, t_vector velocity, t_list *entity_list, t_data *data)
{
	t_rectangle	*colliding_actor;
	unsigned int color;

	draw_rec(*actor, data->buffer, 0xFF);
	colliding_actor = get_colliding_actor(entity_list, actor, velocity);
	draw_rays(*actor, vector_to_point(velocity), colliding_actor, data);
	if (colliding_actor && is_colliding(actor, velocity, colliding_actor))
	{
		velocity = solve_collision (actor, velocity, colliding_actor);
		color = 0x30ff0000;
	}
	else
		color = 0x00ffffff;
	actor->pos = point_add(actor->pos, vector_to_point(velocity));
	draw_rec(*actor, data->buffer, color);
}

t_vector	calc_movement(t_data *data)
{
	t_vector	mov;

	mov = vector2((data->input.right - data->input.left) * 3, (data->input.down - data->input.up) * 3);
	if (mov.x && mov.y)
		mov = vector_multiply(mov, 0.70710678118);
	return (mov);
}

void	player_controller(t_data *data)
{
	t_vector	movement;

	movement = calc_movement(data);
	move_and_collide(&data->raycaster_struct->square, movement, data->raycaster_struct->rec_list, data);
}
