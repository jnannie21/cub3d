/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_exp10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:14:26 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 21:30:38 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_count_exp10(double d)
{
	int		pow;

	if (ft_is_double_special(d) || d == 0)
		return (0);
	if (d < 0)
		d *= (-1);
	pow = 0 - (d < 1);
	if (d >= 1)
		while ((d /= 10) >= 1)
			pow++;
	else
		while ((d *= 10) < 1)
			pow--;
	return (pow);
}
