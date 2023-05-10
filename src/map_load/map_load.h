/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:44:48 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/10 00:13:12 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_LOAD_H
# define MAP_LOAD_H

# include "../../so_long.h"
# include "../../libft/libft.h"
# include "map_struct.h"

t_map	*map_load(char *filepath);
t_map	*map_free(t_map **map);
void	enemy_free(void *enemy);

#endif
