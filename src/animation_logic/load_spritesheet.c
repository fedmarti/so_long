/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_spritesheet.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:14:11 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/08 23:23:46 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation_structs.h"
#include "../../libft/libft.h"
#include "../graphics_logic/graphics.h"
#include "../graphics_logic/graphics_internal.h"

void	advance_to_next_field(char **file, int *i, int *j, char *field_tag);
int		get_field_lenght(char **file, int i, int j);
void	next_char(char **file, int *i, int *j);
void	copy_field_content(char **src, int i, int j, char *dest);

void	skip_chars(char **file, int *i, int *j, char *charset)
{
	unsigned short	r;
	bool			found;

	if (!charset)
		return ;
	while (file[*j])
	{
		r = 0;
		found = false;
		while (charset[r] && !found)
		{
			if (file[*j][*i] == charset[r] || file[*j][*i] == '\0')
				found = true;
			r++;	
		}
		if (!found)
				break ;
		next_char(file, i, j);
	}
}

t_point	get_img_offset(char **file, int i, int j, int path_len)
{
	t_point	offset;

	offset = (t_point){0, 0};
	while (path_len--)
		next_char(file, &i, &j);
	skip_chars(file, &i, &j, " '\n,");
	if (!file[j] || ft_strncmp(&file[j][i], "offset:(", ft_strlen("offset:(")))
		return (offset);
	advance_to_next_field(file, &i, &j, "(");
	skip_chars(file, &i, &j, " '\n,");
	if (!file[j] || ft_strncmp(&file[j][i], "x:'", ft_strlen("x:'")))
		return (offset);
	advance_to_next_field(file, &i, &j, "'");
	offset.x = ft_atoi(&file[j][i]);
	advance_to_next_field(file, &i, &j, "'");
	skip_chars(file, &i, &j, " '\n,");
	if (!file[j] || ft_strncmp(&file[j][i], "y:'", ft_strlen("y:'")))
		return (offset);
	advance_to_next_field(file, &i, &j, "'");
	offset.y = ft_atoi(&file[j][i]);
	return (offset);
}

t_image	*read_sprite(char **file, int i, int j, void *mlx)
{
	size_t	path_len;
	char	*sprite_path;
	t_image	*img;

	path_len = (size_t)get_field_lenght(file, i, j);
	sprite_path = ft_calloc(path_len + 1, sizeof(char));
	if (!sprite_path)
		return (NULL);
	copy_field_content(file, i, j, sprite_path);
	img = ft_calloc(1, sizeof(*img));
	img = image_init_xpm(img, sprite_path, mlx);
	img->offset = get_img_offset(file, i, j, path_len);
	free(sprite_path);
	return (img);
}

void	ft_lstclear_img(t_list **lst, void *mlx)
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		img_free((*lst)->content, mlx);
		free(*lst);
		*lst = temp;
	}
	lst = NULL;
}

t_list	*get_sprite_list(char **file, void *mlx)
{
	int		i;
	int		j;
	t_image	*content;
	t_list	*list;
	t_list	*temp_node;

	j = 1;
	i = 0;
	list = NULL;
	advance_to_next_field(file, &i, &j, "sprites:[{path:'");
	while (file[j])
	{
		content = read_sprite(file, i, j, mlx);
		if (content)
		{
			temp_node = ft_lstnew(content);
			if (temp_node)
				ft_lstadd_back(&list, temp_node);
			else
				break ;
		}
		advance_to_next_field(file, &i, &j, "path:'");
	}
	return (list);
}

t_point	get_spritesheet_size(t_list	*sprite_list)
{
	t_point	size;

	size = (t_point){0, 0};
	while (sprite_list)
	{
		size.y += ((t_image *)sprite_list->content)->size.y;
		if (size.x < ((t_image *)sprite_list->content)->size.x)
			size.x = ((t_image *)sprite_list->content)->size.x;
		sprite_list = sprite_list->next;
	}
	return (size);
}

void	sprite_array_init(t_array *sprites, t_list *sprite_list)
{
	if (sprites->arr)
		free(sprites->arr);
	sprites->n_members = (size_t)ft_lstlen(sprite_list);
	sprites->member_size = sizeof(t_img_fraction);
	if (sprites->n_members == 0)
		return ;
	sprites->arr = ft_calloc(sprites->n_members, sprites->member_size);
	if (!sprites->arr)
	{
		sprites->n_members = 0;
		return ;
	}
}

void	print_now(t_image	*img, t_point	pos);

void	copy_into_spritesheet(t_image *spritesheet, t_image *sprite, t_point position)
{
	position = point_subtract(position, sprite->offset);
	blend_images(sprite, spritesheet, position, overlay);
}

t_image \
	*spritelist_to_spritesheet(t_list *sprite_list, void *mlx, t_array *sprites)
{
	t_image	*spritesheet;
	t_point	size;
	t_point	position;
	t_image	*temp;
	size_t	i;

	size = get_spritesheet_size(sprite_list);
	if (size.x == 0 || size.y == 0)
		return (NULL);
	spritesheet = image_init_color(size.x, size.y, mlx, 0);
	if (!spritesheet)
		return (NULL);
	position = (t_point){0, 0};
	sprite_array_init(sprites, sprite_list);
	i = 0;
	while (sprite_list)
	{
		copy_into_spritesheet(spritesheet, sprite_list->content, position);
		temp = sprite_list->content;
		((t_img_fraction *)sprites->arr)[i] = \
		get_img_fraction(spritesheet, temp->size, temp->offset, position);
		position.y += ((t_image *)sprite_list->content)->size.y;
		sprite_list = sprite_list->next;
		i++;
	}
	return (spritesheet);
}

void	load_spritesheet(char **file, t_anim_data **animation_struct, void *mlx)
{
	t_list	*sprite_list;

	sprite_list = get_sprite_list(file, mlx);
	if (!sprite_list)
		return ;
	if ((*animation_struct)->spritesheet)
		free((*animation_struct)->spritesheet);
	(*animation_struct)->spritesheet = \
	spritelist_to_spritesheet(sprite_list, mlx, &(*animation_struct)->sprites);
	ft_lstclear_img(&sprite_list, mlx);
}

// sprites:[{path:'', path:'',....}]