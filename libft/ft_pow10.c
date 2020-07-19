/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:41:05 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/03 14:39:02 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double					ft_pow10(int n)
{
	double			res;
	double			multiplier;

	multiplier = 10;
	if (n < 0)
	{
		multiplier = 0.1;
		n *= (-1);
	}
	res = 1;
	while (n--)
		res *= multiplier;
	return (res);
}
