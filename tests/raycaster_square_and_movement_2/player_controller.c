/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:03:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/17 13:58:12 by fedmarti         ###   ########.fr       */
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

t_hit	rec_shoot_ray(t_rectangle *actor, t_point direction_vector, t_rectangle *target)
{
	t_hit		hit;
	t_rectangle	big_rec;
	t_point		starting_point;
	
	big_rec.pos = point_subtract(target->pos, point_multiply(actor->size, 0.5));
	big_rec.size = point_add(actor->size, target->size);
	starting_point = point_add(actor->pos, point_multiply(actor->size, 0.5));
	hit = raycast_to_rectangle(starting_point, point_add(starting_point,\
	direction_vector), big_rec.pos, big_rec.size);
	return (hit);
}

void ft_lst_insert_when(t_list **list, t_list *new_node, bool (*comparison)(void *, void *))
{
	t_list	*temp_node;
	t_list	*prev_node;
	
	temp_node = *list;
	prev_node = NULL;
	while (temp_node && !comparison(new_node->content, temp_node->content))
	{
		prev_node = temp_node;
		temp_node = temp_node->next;
	}
	if (!prev_node)
		*list = new_node;
	else
		prev_node->next = new_node;
	new_node->next = temp_node;
}

void	ft_lst_insert_n(t_list **list, t_list *new, unsigned short n)
{
	unsigned short i;
	t_list	*temp;
	t_list	*prev;

	temp = *list;
	prev = NULL;
	i = 0;
	while (temp && i != n)
	{
		prev = temp;
		temp = temp->next;
		i++;
	}
	if (!prev)
		*list = new;
	else
		prev->next = new;
	new->next = temp;
}

void	add_to_collision_list(t_list **collision_list, t_rectangle *rec, unsigned short *hit_dist, unsigned short arr_len)
{
	unsigned short	list_position;
	unsigned short	current_hit_dist;
	t_list			*new_node;

	list_position = 0;
	current_hit_dist = hit_dist[arr_len - 1];
	while (arr_len--)
	{
		if (*hit_dist < current_hit_dist)
			list_position++;
		hit_dist++;
	}
	new_node = ft_lstnew(rec);
	if (!new_node)
		return ;
	ft_lst_insert_n(collision_list, new_node, list_position);
}

t_list	*get_colliding_actors(t_list *entity_list, t_rectangle *actor, t_vector vel)
{
	// t_list			*temp_node;
	unsigned short	hit_distance[5];
	unsigned short	i;
	t_hit			hit;
	t_list			*collision_list;

	i = 0;
	collision_list = NULL;
	while (entity_list)
	{
		hit = rec_shoot_ray(actor, vector_to_point(vel), (t_rectangle *)entity_list->content);
		if (hit.collision)
		{
			hit_distance[i] = line_len((t_line){hit.origin, hit.intersection});
			i++;
			add_to_collision_list(&collision_list, (t_rectangle *)entity_list->content, hit_distance, i);
		}
		// temp_node = entity_list->next;
		// ft_lstdelone(entity_list , ft_do_nothing);
		// entity_list = temp_node;
		entity_list = entity_list->next;
	}
	return (collision_list);
}

void	draw_rec(t_rectangle rec, t_image *img, unsigned int color);

void	draw_ray_and_rec(t_rectangle rec, t_point velocity, t_rectangle *target, t_data *data)
{
	t_hit		hit;
	t_rectangle	big_rec;
	t_point	starting_point = point_add(rec.pos, point_multiply(rec.size, 0.5));

	if (!target)
	{
		for (int i = 0; i < 3; i++)
			draw_line_gba(data->buffer, starting_point, point_add(starting_point, velocity), 0xFFFFFF);
		return ;
	}
	big_rec = (t_rectangle){point_subtract(target->pos, point_multiply(rec.size, 0.5)), point_add(rec.size, target->size)};
	hit = raycast_to_rectangle(starting_point, point_add(starting_point,\
	velocity), big_rec.pos, big_rec.size);
	draw_rec(big_rec, data->buffer, 0x888888);	
	draw_line_gba(data->buffer, hit.origin, hit.intersection, 0x30ff0000);
}


void	move_and_collide(t_rectangle *actor, t_vector velocity, t_list *entity_list, t_data *data)
{
	t_list			*colliding_actors;
	t_list			*temp_node;
	t_rectangle		*temp_rec;
	unsigned int	color;

	color = 0x00ffffff;
	draw_rec(*actor, data->buffer, 0xFF);
	colliding_actors = get_colliding_actors(entity_list, actor, velocity);
	while (colliding_actors)
	{
		temp_rec = (t_rectangle *)colliding_actors->content;
		draw_ray_and_rec(*actor, vector_to_point(velocity), temp_rec, data);
		if (is_colliding(actor, velocity, temp_rec))
		{
			velocity = solve_collision (actor, velocity, temp_rec);
			color = 0x30ff0000;
		}
		temp_node = colliding_actors;
		colliding_actors = colliding_actors->next;
		ft_lstdelone(temp_node, ft_do_nothing);
	}
	actor->pos = point_add(actor->pos, vector_to_point(velocity));
	draw_rec(*actor, data->buffer, color);
	// ft_lstclear(&entity_list, ft_do_nothing);
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
