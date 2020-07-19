/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 12:38:26 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/13 16:47:13 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (s == 0 || f == 0)
		return (0);
	str = ft_strdup(s);
	if (str == 0)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		str[i] = f(i, str[i]);
		if (str[i] == 0)
		{
			free(str);
			return (0);
		}
		i++;
	}
	return (str);
}
