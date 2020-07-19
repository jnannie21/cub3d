/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 10:58:19 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/06 11:05:00 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*last_str;

	str = (char *)s;
	last_str = 0;
	while (*str != '\0')
	{
		if (*str == (char)c)
			last_str = str;
		str++;
	}
	if ((char)c == '\0')
		return (str);
	return (last_str);
}
