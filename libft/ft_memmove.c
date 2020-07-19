/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 01:59:48 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/13 22:00:00 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** when both dest and src == 0 original function returns 0
*/

static int	is_dest_inside_src(void *dest, const void *src, size_t n)
{
	return ((char *)dest > (char *)src && (char *)dest < ((char *)(src) + n));
}

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;

	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	if (is_dest_inside_src(dest, src, n))
	{
		while (n--)
			((char *)dest)[n] = ((char *)src)[n];
	}
	else
	{
		while (i++ < n)
			((char *)dest)[i - 1] = ((char *)src)[i - 1];
	}
	return (dest);
}
