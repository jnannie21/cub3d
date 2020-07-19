/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 01:50:37 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/05 13:32:02 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strpbrk(const char *s, const char *accept)
{
	while (*s && (ft_strchr(accept, *s) == 0))
		s++;
	if (*s)
		return ((char *)s);
	return (0);
}
