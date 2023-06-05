/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 21:08:51 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/01 21:50:45 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_plus.h"

//returns num limiting it to the given range
//does not perform checks on the input and will break with min > max
int	ft_clamp(int num, int min, int max)
{
	return(num * (num >= min && num <= max) + min * (num < min) + max * (num > max));
}

//clamps the number regardless of sign
//the return value is signed, however.
//does not perform checks on the input and will break with wrong inputs, such as
// |min| > |max|
int ft_abs_clamp(int num, int min, int max)
{
	return (num * (ft_abs(num) >= ft_abs(min) && ft_abs(num) <= ft_abs(max)) \
	+ min * (ft_abs(num) < ft_abs(min)) + max * (ft_abs(num) > ft_abs(max)));
}

