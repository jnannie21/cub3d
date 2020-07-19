/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_itoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:20:01 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 21:22:39 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_u_itoa_base(unsigned long long n, int base)
{
	char				*last_digit;
	char				*result;
	char				*remains;

	last_digit = ft_itoa_base(n % base, base);
	if (n / base != 0)
		remains = ft_itoa_base(n / base, base);
	else
		remains = ft_strdup("");
	result = 0;
	if (last_digit && remains)
		result = ft_strjoin(remains, last_digit);
	free(remains);
	free(last_digit);
	return (result);
}
