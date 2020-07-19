/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 09:34:27 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 22:12:22 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			count_num(long long n, int base)
{
	int		i;

	i = 1;
	while ((n = n / base) != 0)
		i++;
	return (i);
}

char				*ft_itoa_base(long long n, int base)
{
	char	*s;
	int		num;

	num = count_num(n, base);
	if (!(s = ft_calloc((num + 1 + (n < 0)), sizeof(char))))
		return (0);
	s[0] = (n < 0) ? '-' : '\0';
	while (num--)
	{
		s[num + (n < 0)] = (n < 0) ? (n % base) * (-1) + '0' : n % base + '0';
		if (s[num + (n < 0)] > '9')
			s[num + (n < 0)] += 7;
		n /= base;
	}
	return (s);
}
