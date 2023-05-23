/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:56:18 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/23 01:24:23 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PLUS_H
# define LIBFT_PLUS_H

# include "../libft/libft.h"
# include "../src/t_point/point.h"
# include <stdbool.h>

int		ft_max(int a, int b);
int		ft_min(int a, int b);
int		ft_abs(int a);
int		abs_max(int a, int b);
int		abs_min(int a, int b);
int		abs_max_signed(int a, int b);
int		abs_min_signed(int a, int b);
void	ft_do_nothing(void *p);
void	ft_do_nothing_2(void *p, void *p2);
int		ft_lstlen(t_list *lst);
void	*ft_free_matrix(void ***pointer, size_t n_members);
// allocates using ft_calloc a pointer array of size (y + 1* sizeof(void *))
// and then allocates (x * member_size) y times
// returns the null terminated matrix
void	**ft_matrix_init(size_t x_size, size_t y_size, size_t member_size);
t_point	ft_get_next_direction(void);
void	*ft_get_directions(t_point *directions);
bool	ft_is_in_list(t_list *list, void *content, size_t content_size);
void	ft_lst_iteri_2(t_list *list, void (*foo)(void *, void *), void *arg);
void	ft_lstclear_2(t_list **lst, void (*del)(void *, void *), void *arg);


#endif
