/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 04:25:28 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 22:09:19 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MININTVALUE -2147483648

static int		count_num(int n)
{
	int		num;

	num = 1;
	while ((int)(n / ft_pow10(num)) != 0)
		num++;
	return (num);
}

char			*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		num;
	int		is_negative;

	is_negative = (n < 0);
	num = count_num(n);
	s = malloc((num + is_negative + 1) * sizeof(char));
	if (s == 0)
		return (0);
	if (n == MININTVALUE)
	{
		ft_strlcpy(s, "-2147483648", 12);
		return (s);
	}
	if (is_negative)
	{
		s[0] = '-';
		n *= (-1);
	}
	i = is_negative;
	while (num--)
		s[i++] = ((int)(n / ft_pow10(num))) % 10 + 48;
	s[i] = '\0';
	return (s);
}
