/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 11:50:55 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/17 03:49:03 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*substr;
	size_t	i;

	if (s == 0)
		return (0);
	str = (char *)s;
	while (str < (s + start))
		if (*str++ == '\0')
			return (ft_strdup(""));
	if (ft_strlen(str) < len)
		len = ft_strlen(str);
	if ((substr = malloc(len + 1)) == 0)
		return (0);
	i = 0;
	while (i++ < len)
		if ((substr[i - 1] = str[i - 1]) == '\0')
			return (substr);
	substr[len] = '\0';
	return (substr);
}
