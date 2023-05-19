/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:56:18 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/17 19:08:00 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PLUS_H
# define LIBFT_PLUS_H

# include "../libft/libft.h"
# include "../src/t_point/point.h"

int		ft_max(int a, int b);
int		ft_min(int a, int b);
int		ft_abs(int a);
int		abs_max(int a, int b);
int		abs_min(int a, int b);
int		abs_max_signed(int a, int b);
int		abs_min_signed(int a, int b);
void	ft_do_nothing(void *p);
int		ft_lstlen(t_list *lst);
void	*ft_free_matrix(void ***pointer, size_t n_members);
// allocates using ft_calloc a pointer array of size (y + 1* sizeof(void *))
// and then allocates (x * member_size) y times
// returns the null terminated matrix
void 	**ft_matrix_init(size_t x_size, size_t y_size, size_t member_size);
t_point	ft_get_next_direction(void);
void	*ft_get_directions(t_point *directions);

#endif
