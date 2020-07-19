/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctomb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:13:39 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/08 22:19:42 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_wctomb(char *s, wchar_t wc)
{
	int		octets;
	int		n;

	octets = 1 + (wc > 0x0000007F) + (wc > 0x000007FF) + (wc > 0x0000FFFF);
	n = octets;
	while (--n)
	{
		s[n] = s[n] | 0x80 | ((char)wc & 0x3F);
		wc = wc >> 6;
	}
	if (octets == 1)
		s[0] = (char)wc;
	else
		s[0] = (char)wc | ~(0xFF >> octets);
	return (octets);
}
