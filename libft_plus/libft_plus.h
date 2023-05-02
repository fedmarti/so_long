/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:56:18 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/02 23:49:31 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PLUS_H
# define LIBFT_PLUS_H

# include "../libft/libft.h"

int		ft_max(int a, int b);
int		ft_max(int a, int b);
int		ft_abs(int a);
int		abs_max(int a, int b);
int		abs_min(int a, int b);
int		abs_max_signed(int a, int b);
int		abs_min_signed(int a, int b);
void	ft_do_nothing(void *p);
int		ft_lstsize(t_list *lst);
void	*ft_free_matrix(void ***pointer, size_t n_members);

#endif
