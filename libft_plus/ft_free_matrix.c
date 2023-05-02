/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:05:48 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/02 23:17:18 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_plus.h"

void	*ft_free_matrix(void ***pointer, size_t n_members)
{
	size_t	i;

	i = 0;
	while (i <= n_members)
	{
		free((*pointer)[i]);
		i++;
	}
	free(*pointer);
	*pointer = NULL;
	return (NULL);
}
