/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_double_special.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:17:06 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 21:17:23 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_is_double_special(double d)
{
	if (*((unsigned long *)&d) == POSITIVE_INFINITY ||
		*((unsigned long *)&d) == NEGATIVE_INFINITY ||
		(*((unsigned long *)&d) >= MIN_PNAN &&
		*((unsigned long *)&d) <= MAX_PNAN) ||
		(*((unsigned long *)&d) >= MIN_NNAN &&
		*((unsigned long *)&d) <= MAX_NNAN))
		return (1);
	return (0);
}
