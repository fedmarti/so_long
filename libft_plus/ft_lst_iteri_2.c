/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iteri_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:01:44 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/23 01:03:33 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_plus.h"

void	ft_lst_iteri_2(t_list *list, void (*foo)(void *, void *), void *arg)
{
	while (list)
	{
		foo(list->content, arg);
		list = list->next;
	}
}
