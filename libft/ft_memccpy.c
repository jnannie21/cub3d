/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:31:45 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/05 04:33:28 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n-- > 0)
	{
		*((char *)dest) = *((char *)src);
		if (*((char *)src) == (char)c)
			return ((char *)dest + 1);
		dest = (char *)dest + 1;
		src = (char *)src + 1;
	}
	return (0);
}
