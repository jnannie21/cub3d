/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:50:20 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/08 17:36:52 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_in(char ch, char const *set)
{
	char	*s;

	s = (char *)set;
	while (*s != '\0')
	{
		if (*s == ch)
			return (1);
		s++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*str;
	size_t	len;

	if (s1 == 0 || set == 0)
		return (0);
	start = (char *)s1;
	while (is_in(*start, set))
		start++;
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (end > start && is_in(*end, set))
		end--;
	len = end - start + 2;
	str = malloc(len);
	if (str == 0)
		return (0);
	ft_strlcpy(str, start, len);
	return (str);
}
