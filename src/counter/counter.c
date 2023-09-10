/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:56:48 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/10 19:04:33 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "counter.h"
#include "../../so_long.h"
#include "../graphics_logic/graphics_internal.h"

void	*counter_free(void **counter, void *mlx)
{
	struct s_counter	*c;

	c = *counter;
	if (c->screen_space)
		img_free(c->screen_space, mlx);
	if (c->sprite)
		img_free(c->sprite, mlx);
	free(c);
	*counter = NULL;
	return (NULL);
}

void	*counter_init(void *mlx)
{
	struct s_counter	*counter;
	t_image				*temp;

	counter = ft_calloc(1, sizeof(*counter));
	if (!counter)
		return (NULL);
	counter->sprite = ft_calloc(1, sizeof(*counter->sprite));
	counter->sprite = image_init_xpm(counter->sprite, COUNTER_PATH, mlx);
	if (!counter->sprite)
		return (counter_free((void **)&counter, mlx));
	temp = image_init_color(counter->sprite->size.x, counter->sprite->size.y, \
	mlx, 0x99000000);
	if (!temp)
		return (counter_free((void **)&counter, mlx));
	blend_images(temp, counter->sprite, point2(0, 0), t_multiply);
	img_free(temp, mlx);
	counter->screen_space = image_init_color(counter->sprite->size.x * 2, \
	counter->sprite->size.y / 11, mlx, 0xFF000000);
	if (!counter->screen_space)
		return (counter_free((void **)&counter, mlx));
	return (counter);
}

void	counter_add(double distance, void *counter)
{
	struct s_counter	*c;

	c = counter;
	if (distance < 0)
		distance *= -1;
	c->distance_travelled += distance;
}

t_image	*get_counter_graphics(void *counter)
{
	struct s_counter	*c;
	double				onscreen_val;
	double				counter_height;
	t_img_fraction		frac;

	c = counter;
	put_solid_color(c->screen_space, 0xFFFFFFFF);
	onscreen_val = c->distance_travelled / TILE_SIZE;
	counter_height = onscreen_val - (double)((int)onscreen_val / 10 * 10);
	counter_height = c->sprite->size.y - (c->screen_space->size.y \
	* (counter_height + 1));
	frac = get_img_fraction(c->sprite, (t_point){c->sprite->size.x, \
	c->screen_space->size.y}, (t_point){0, 0}, (t_point){0, counter_height});
	blend_img_fraction(&frac, c->screen_space, (t_point){c->sprite->size.x, 0}, \
	t_overlay);
	onscreen_val /= 10;
	counter_height = onscreen_val - (double)((int)onscreen_val / 10 * 10);
	counter_height = c->sprite->size.y - (c->screen_space->size.y \
	* (counter_height + 1));
	frac = get_img_fraction(c->sprite, (t_point){c->sprite->size.x, \
	c->screen_space->size.y}, (t_point){0, 0}, (t_point){0, counter_height});
	blend_img_fraction(&frac, c->screen_space, (t_point){0, 0}, t_overlay);
	return (c->screen_space);
}
