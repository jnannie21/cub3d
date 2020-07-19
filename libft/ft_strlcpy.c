/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 09:52:14 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/06 02:01:33 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		i;

	i = 0;
	if (size != 0)
	{
		while (i < (size - 1))
		{
			if ((dst[i] = src[i]) == '\0')
				return (i);
			i++;
		}
		dst[size - 1] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}
