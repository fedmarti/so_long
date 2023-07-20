/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_load.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:37:31 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/21 00:45:24 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "animation_structs.h"
#include "../../so_long.h"

t_animation	*new_animation(char **anim_file, int i, int j);
void		advance_to_next_field(char **file, int *i, int *j, char *field_tag);
void		load_spritesheet(char **file, \
t_anim_data **animation_struct, void *mlx);

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
		content = new_animation(file, i, j);
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
	add_animations(anim_struct, animation_list);
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
	ft_free_matrix(&file, ft_matrix_size(file));
}

/*\
Animation data file
sprites:[{path:'', path:'',....}]
animation_name:['']
frames:[{sprite:'(num that indicates the loaded sprites)',duration:'', ...}]
type:['']*/