/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 04:23:38 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/22 19:49:12 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "actor_structs.h"
#include <stdlib.h>

void	actor_free(t_actor	**actor)
{
	if (!*actor)
		return ;
	if ((*actor)->additional_struct)
		free((*actor)->additional_struct);
	free(*actor);
	*actor = NULL;
}
