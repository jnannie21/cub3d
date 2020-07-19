/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 07:17:58 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 21:29:50 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char				*special_cases(double d)
{
	if (*((unsigned long *)&d) == POSITIVE_INFINITY)
		return (ft_strdup("inf"));
	else if (*((unsigned long *)&d) == NEGATIVE_INFINITY)
		return (ft_strdup("-inf"));
	else if (*((unsigned long *)&d) >= MIN_PNAN &&
			*((unsigned long *)&d) <= MAX_PNAN)
		return (ft_strdup("nan"));
	else if (*((unsigned long *)&d) >= MIN_NNAN &&
			*((unsigned long *)&d) <= MAX_NNAN)
		return (ft_strdup("-nan"));
	return (0);
}

static double			process_negative(double d, char **temp)
{
	if (d < 0 || *((unsigned long *)&d) == MINUS_ZERO)
	{
		**temp = '-';
		(*temp)++;
		d *= (-1);
	}
	return (d);
}

char					*ft_ftoa(double d, int precision)
{
	char			*result;
	char			*temp;
	int				digit;
	int				sum_len;
	int				integer_len;

	if (ft_is_double_special(d))
		return (special_cases(d));
	if ((integer_len = ft_count_exp10(d) + 1) <= 0)
		integer_len = 1;
	sum_len = integer_len + precision;
	result = ft_calloc(sum_len + (d < 0) + (precision > 0) + 1, sizeof(char));
	temp = result;
	d = process_negative(d, &temp);
	d = d / ft_pow10(sum_len - precision - 1);
	while (sum_len--)
	{
		digit = d;
		*temp++ = digit + '0';
		if (precision && sum_len == precision)
			*temp++ = '.';
		d -= digit;
		d *= 10;
	}
	return (result);
}
