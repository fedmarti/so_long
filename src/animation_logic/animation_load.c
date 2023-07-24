/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_load.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:37:31 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/24 23:23:06 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "animation_structs.h"
#include "../../so_long.h"

t_animation	*new_animation(char **anim_file, int i, int j, t_array *sprite_arr);
void		advance_to_next_field(char **file, int *i, int *j, char *field_tag);
void		load_spritesheet(char **file, \
t_anim_data **animation_struct, void *mlx);

// static void	ani_free(void *ani)
// {
// 	t_animation	**animation;

// 	animation = ani;
// 	if (!*animation)
// 		return ;
// 	if ((*animation)->name)
// 		free((*animation)->name);
// 	*animation = NULL;
// }

void	parse_animation_data_file(char **file, \
t_anim_data **anim_struct, void *mlx)
{
	int			i;
	int			j;
	t_list		*animation_list;
	t_list		*temp_node;
	t_animation	*content;

	animation_list = NULL;
	i = 0;
	j = 1;
	load_spritesheet(file, anim_struct, mlx);
	advance_to_next_field(file, &i, &j, "animation_name:['");
	while (file[j])
	{
		content = new_animation(file, i, j, &(*anim_struct)->sprites);
		if (content)
		{
			temp_node = ft_lstnew(content);
			if (temp_node)
				ft_lstadd_back(&animation_list, temp_node);
			else
				break ;
		}
		advance_to_next_field(file, &i, &j, "animation_name:['");
	}
	(*anim_struct)->animations = ft_lst_to_array(&animation_list, sizeof(t_animation), free);
}

void	read_animation_file(char *filepath, \
t_anim_data **anim_struct, void *mlx)
{
	char	**file;

	file = ft_read_file(filepath);
	if (!file)
		return ;
	if (!ft_strncmp(*file, ANIMATION_HEADER, ft_strlen(ANIMATION_HEADER)))
		parse_animation_data_file(file, anim_struct, mlx);
	ft_free_matrix((void ***)&file, ft_matrix_size((void **)file));
}

/*\
Animation data file
sprites:[{path:'', path:'',....}]
animation_name:['']
frames:[{sprite:'(num that indicates the loaded sprites)',duration:'', ...}]
type:['']*/