/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:14:00 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/24 23:05:04 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation_structs.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include "../graphics_logic/graphics_structs.h"
#include <sys/time.h>


void	*animation_free(t_animation **animation);

void	next_char(char **file, int *i, int *j)
{
	if (file[*j][*i] == '\0')
	{
		*i = 0;
		*j = *j + 1;
	}
	else
		*i = *i + 1;
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

	name = ft_calloc((size_t)get_field_lenght(file, i, j) + 1, sizeof(char));
	if (!name)
		return (NULL);
	copy_field_content(file, i, j, name);
	return (name);
}

void	advance_to_next_field(char **file, int *i, int *j, char *field_tag)
{
	size_t	tag_len;

	tag_len = ft_strlen(field_tag);
	// while (file[*j] && file[*j][*i] != ']')
		// next_char(file, i, j);
	while (file[*j])
	{
		if (!ft_strncmp(field_tag, &file[*j][*i], tag_len))
		{
			while(tag_len--)
				next_char(file, i, j);
			return ;
		}
		next_char(file, i, j);
	}
}

t_frame	*new_frame(char **file, int *i, int *j, t_array	*sprite_arr)
{
	t_frame	*new_frame;
	int		sprite_num;

	new_frame = ft_calloc(1, sizeof(*new_frame));
	if (!new_frame)
		return (NULL);
	sprite_num = ft_atoi(&file[*j][*i]);
	if ((size_t)sprite_num < sprite_arr->n_members)
		new_frame->img = &((t_img_fraction *)sprite_arr->arr)[sprite_num];
	advance_to_next_field(file, i, j, "duration:'");
	if (file[*j])
		new_frame->duration = ft_atoi(&file[*j][*i]);
	return (new_frame);
}

t_list	*new_frame_node(char **anim_file, int *i, int *j, t_array *arr)
{
	t_frame	*frame;
	t_list	*node;

	frame = new_frame(anim_file, i, j, arr);
	if (!frame)
		return (NULL);
	node = ft_lstnew(frame);
	if (!node)
		free(frame);
	return (node);
}

// t_array	get_animation_frames(char **anim_file, int i, int j, t_array *arr)
// {
// 	t_list	*list;
// 	t_list	*temp;

// 	list = NULL;
// 	advance_to_next_field(anim_file, &i, &j, "sprite:'");
// 	while (anim_file[j] && anim_file[j][i] != ']')
// 	{
// 		temp = new_frame_node(anim_file, &i, &j, arr);
// 		if (!temp)
// 		{
// 			ft_lstclear(&list, free);
// 			return ((t_array){(void *)0, 0, 0});
// 		}
// 		else
// 			ft_lstadd_back(&list, temp);
		
// 		advance_to_next_field(anim_file, &i, &j, "sprite:'");
// 	}
// 	return (ft_lst_to_array(&list, sizeof(t_frame), free));
// }


t_array	get_animation_frames(char **anim_file, int i, int j, t_array *arr)
{
	t_list	*list;
	t_list	*temp;

	list = NULL;
	while (anim_file[j] && anim_file[j][i] != '}')
	{
		advance_to_next_field(anim_file, &i, &j, "sprite:'");
		temp = new_frame_node(anim_file, &i, &j, arr);
		if (!temp)
		{
			ft_lstclear(&list, free);
			return ((t_array){(void *)0, 0, 0});
		}
		else
			ft_lstadd_back(&list, temp);
		advance_to_next_field(anim_file, &i, &j, "'");
		while (anim_file[j] && (anim_file[j][i] == '\n' || anim_file[j][i] == ' ' || anim_file[j][i] == '\''))
			next_char(anim_file, &i, &j);
	}
	return (ft_lst_to_array(&list, sizeof(t_frame), free));
}

suseconds_t	get_aniamtion_duration(t_animation *anim)
{
	suseconds_t	tot_duration;
	t_frame		*frame_array;
	size_t		i;

	if (!anim->frames.arr)
		return (0);
	tot_duration = 0;
	i = 0;
	frame_array = anim->frames.arr;
	while (i < anim->frames.n_members)
	{
		tot_duration += frame_array[i].duration;
		i++;
	}
	return (tot_duration);
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
	advance_to_next_field(anim_file, &i, &j, "frames:[{");
	if (!anim_file[j])
		return (animation_free(&animation));
	animation->frames = get_animation_frames(anim_file, i, j, sprite_arr);
	if (!animation->frames.arr)
		return (animation_free(&animation));
	animation->tot_duration = get_aniamtion_duration(animation);
	advance_to_next_field(anim_file, &i, &j, "type:['");
	if (anim_file[j])
		animation->type = ft_atoi(&anim_file[j][i]);
	else
		animation->type = 0;
	return (animation);
}

/*\
format for the file:

Animation data file
sprites:[{path:'', path:'',....}]
animation_name:['']
frames:[{sprite:'(num that indicates the loaded sprites)', duration:''},{...}]
type:['']*/
