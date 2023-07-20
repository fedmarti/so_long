/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:14:00 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/20 17:22:40 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation_structs.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include "../graphics_logic/graphics_structs.h"
#include <sys/time.h>

void	next_char(char **file, int *i, int *j)
{
	if (file[*j][*i] == '\0')
	{
		*i = 0;
		*j++;
	}
	else
		*i++;
}

int	get_field_lenght(char **file, int i, int j)
{
	int	len;

	len = 0;
	while (file[j][i] != 39)
	{
		if (file[j][i] != '\n' && file[j][i] != '\0')
			len++;
		next_char(file, &i, &j);
	}
	return (len);
}

void	copy_field_content(char **src, int i, int j, char *dest)
{
	while (src[j][i] != 39)
	{
		if (src[j][i] != '\n' && src[j][i] != '\0')
		{
			*dest = src[j][i];
			dest++;
		}
		next_char(src, &i, &j);
	}
}

static char	*get_animation_name(char **file, int i, int j)
{
	char	*name;

	name = ft_calloc((size_t)get_field_lenght(name, i, j) + 1, sizeof(char));
	if (!name)
		return (NULL);
	copy_field_content(file, i, j, name);
	return (name);
}

void	advance_to_next_field(char **file, int *i, int *j, char *field_tag)
{
	while (file[*j][*i] != ']')
		next_char(file, i, j);
	while (file[*j] && \
	(!ft_strncmp(field_tag, &file[*j][*i], ft_strlen(field_tag))))
		next_char(file, i, j);
}

t_array	get_animation_frames(anim_file, i, j, sprite_arr)
{
	return ((t_array){NULL, 0, 0});
}

void	*animation_free(t_animation **animation)
{
	if (!*animation)
		return ;
	if ((*animation)->name)
		free((*animation)->name);
	if ((*animation)->frames.arr)
		free((*animation)->frames.arr);
	free(*animation);
	*animation = NULL;
	return (NULL);
}

t_animation	*new_animation(char **anim_file, int i, int j, t_array *sprite_arr)
{
	t_animation	*animation;

	animation = ft_calloc(1, sizeof(*animation));
	if (!animation)
		return (NULL);
	animation->name = get_animation_name(anim_file, i, j);
	if (!animation->name)
		return (animation_free(&animation));
	advance_to_next_field(anim_file, &i, &j, "frames:['");
	if (!anim_file[j])
		return (animation_free(&animation));
	animation->frames = get_animation_frames(anim_file, i, j, sprite_arr);
	if (!animation->frames.arr)
		return (animation_free(&animation));
	animation->tot_duration = get_aniamtion_duration(animation);
	advance_to_next_field(anim_file, &i, &j, "type:[");
	animation->type = get_animation_type(anim_file, i, j);
	return (animation);
}

/*\
format for the file:

Animation data file
sprites:[{path:'', path:'',....}]
animation_name:['']
frames:[{sprite:'(num that indicates the loaded sprites)',duration:'', ...}]
type:['']*/
