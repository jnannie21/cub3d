/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 02:03:48 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/17 17:40:05 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		d;
	size_t		s;

	d = 0;
	s = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[d] != '\0' && d < (size - 1))
		d++;
	if (dst[d] != '\0' && d == (size - 1))
		return (size + ft_strlen(src));
	while (d < (size - 1))
	{
		if ((dst[d] = src[s]) == '\0')
			return (d);
		d++;
		s++;
	}
	dst[d] = '\0';
	return (d + ft_strlen(src + s));
}
